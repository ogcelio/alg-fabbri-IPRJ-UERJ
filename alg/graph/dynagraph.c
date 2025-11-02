/*
 * =====================================================================================
 * 
 *        Filename:  dynagraph.c
 * 
 *     Description:  exercise on completely dynamic graph representation
 * 
 *         Version:  1.0
 *         Created:  jun/2019
 *        Revision:  none
 *        Compiler:  gcc
 * 
 *          Author:  Ricardo Fabbri (rfabbri), rfabbri.github.io
 *         Company:  IPRJ/UERJ
 * 
 * =====================================================================================
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct lista *lista_ptr; 
typedef struct no *no_ptr;

// Guarda uma conexao com peso 'peso' ao no 'no'
typedef struct lista { 
  no_ptr no; 
  int peso; 
  struct lista *next; 
} lista;

typedef struct no { 
  char nome[32]; 
  lista *conexoes; 
} no;

// Insere conexao para no na lista de conexoes lst,
// onde a conexao tem peso "peso"
void insere(lista **lst, no_ptr no, int peso) {
   lista *conexao = (lista *) malloc(sizeof(lista));
   conexao->peso = peso; 
   conexao->no = no;     // diz que conexao vai pra B
   conexao->next = *lst; // insere conexao na lista de conexcoes de A
   *lst = conexao;
}
void liga(no_ptr a, no_ptr b, int p) { 
  insere(&a->conexoes, b, p); 
  insere(&b->conexoes, a, p); 
}

#define MAX_NUM_NOS 1000   // maximo numero de nos para componente conexo
int componente_conexo(no_ptr r, int max_conexao, no_ptr nos[], int *n_nos);
int componente_conexo_sem_maximo(no_ptr r, no_ptr nos[], int *n_nos);
void renomeia_friburgo(const no *p_petro);
void deleta_no_grafo(no_ptr r);
int **converte_para_matriz_adjacencia(no_ptr r, no_ptr nos[], int *n_nos);
void imprime_matriz_adjacencia(int **matrix, int n_nos);
void libera_matriz_adjacencia(int **matrix, int n_nos);



// -----------------------------------------------------------------------------
// renomeia_friburgo : altera nome de Friburgo para Nova Friburgo, dado um ponteiro
// para Petropolis

void
renomeia_friburgo(const no *p_petro)
{
  strcpy(p_petro->conexoes->no->conexoes->next->no->nome,"Nova Friburgo");
}

void remove_conexao(lista_ptr *h, const no_ptr r);
// 
// -----------------------------------------------------------------------------
// Remove no
void
deleta_no_grafo(no_ptr r)
{
  // remove todas as conexoes ida e volta
  lista_ptr v = r->conexoes;
  while (v != NULL) {
    remove_conexao(&(v->no->conexoes), r);
    lista_ptr aux = v;
    v = v->next;
    free(aux);
  }
  // nao faz "free" no no em si - deixa o "caller" dar free se quiser
}

// busca por conexao ao no r e deleta da lista
void
remove_conexao(lista_ptr *h, const no_ptr r)
{
  lista_ptr l = *h, prev = l;
  for (; l != NULL && l->no != r; prev = l, l = l->next)
    ;
  if (!l) return;
  if (prev != l) // middle or last element
    prev->next = l->next;
  else // first or one element
    *h = l->next;
  free(l);
}

// -----------------------------------------------------------------------------
int
componente_conexo_sem_maximo(no_ptr r, no_ptr nos[], int *n_nos)
{
  int peso_total = 0;
  if (*n_nos > MAX_NUM_NOS)  { fprintf(stderr,"ERRO"); return -1; }
  nos[(*n_nos)++] = r;
  for (lista_ptr v = r->conexoes; v != NULL; v = v->next) {
    int i = 0;
    for (; i < *n_nos; ++i)
      if (nos[i] == v->no)
        break;
    if (i == *n_nos)  // neighboring node v->no not visited, insert
      peso_total += v->peso + componente_conexo_sem_maximo(v->no, nos, n_nos);
  }
  // peso total apenas de uma arvore que mantem os nos conexos
  // se quiser peso total com ciclos, pode simplesmente usar as conexoes no grafo original.
  // ambas solucoes serao tidas como corretas
  return peso_total;
}

//------------------------------------------------------------------------------
int
componente_conexo(no_ptr r, int max_conexao, no_ptr nos[], int *n_nos)
{
  int peso_total = 0;
  if (*n_nos > MAX_NUM_NOS)  {
    fprintf(stderr,"ERRO");
    return -1;
  }
  nos[(*n_nos)++] = r;
  for (lista_ptr v = r->conexoes; v != NULL; v = v->next) {
    if (v->peso >= max_conexao)
      continue;
    int i = 0;
    for (; i < *n_nos; ++i)
      if (nos[i] == v->no)
        break;
    if (i == *n_nos)  // neighboring node v->no not visited, insert
      peso_total += v->peso + componente_conexo(v->no, max_conexao, nos, n_nos);
  }
  return peso_total;
}


//------------------------------------------------------------------------------
// Helper function to find the index of a node in an array of nodes.
// Returns -1 if not found.
static int
find_node_index(no_ptr node, no_ptr nodes[], int n_nodes)
{
  for (int i = 0; i < n_nodes; i++) {
    if (nodes[i] == node) {
      return i;
    }
  }
  return -1;
}

//------------------------------------------------------------------------------
// Converts the graph to an adjacency matrix.
// The caller is responsible for freeing the returned matrix.
// The node pointers are stored in `nos`, and the number of nodes in `n_nos`.
int **
converte_para_matriz_adjacencia(no_ptr r, no_ptr nos[], int *n_nos)
{
  // 1. Find all nodes in the component and store them in `nos`
  *n_nos = 0;
  componente_conexo_sem_maximo(r, nos, n_nos);
  int num_nodes = *n_nos;

  if (num_nodes == 0) {
    return NULL;
  }

  // 2. Allocate the adjacency matrix
  int **matrix = (int **) malloc(num_nodes * sizeof(int *));
  if (matrix == NULL) {
    fprintf(stderr, "Memory allocation error for matrix\n");
    return NULL;
  }
  for (int i = 0; i < num_nodes; i++) {
    matrix[i] = (int *) calloc(num_nodes, sizeof(int));
    if (matrix[i] == NULL) {
      fprintf(stderr, "Memory allocation error for matrix row\n");
      // Free already allocated memory
      for (int j = 0; j < i; j++) {
        free(matrix[j]);
      }
      free(matrix);
      return NULL;
    }
  }

  // 3. Populate the adjacency matrix
  for (int i = 0; i < num_nodes; i++) {
    no_ptr current_node = nos[i];
    for (lista_ptr v = current_node->conexoes; v != NULL; v = v->next) {
      int j = find_node_index(v->no, nos, num_nodes);
      if (j != -1) {
        matrix[i][j] = v->peso;
      }
    }
  }

  return matrix;
}

//------------------------------------------------------------------------------
// Prints the adjacency matrix.
void
imprime_matriz_adjacencia(int **matrix, int n_nos)
{
  if (matrix == NULL || n_nos == 0) {
    printf("Matrix is empty or invalid.\n");
    return;
  }
  printf("Adjacency Matrix (%dx%d):\n", n_nos, n_nos);
  for (int i = 0; i < n_nos; i++) {
    for (int j = 0; j < n_nos; j++) {
      printf("%d\t", matrix[i][j]);
    }
    printf("\n");
  }
}

//------------------------------------------------------------------------------
// Frees the memory allocated for the adjacency matrix.
void
libera_matriz_adjacencia(int **matrix, int n_nos)
{
  if (matrix == NULL) return;
  for (int i = 0; i < n_nos; i++) {
    free(matrix[i]);
  }
  free(matrix);
}

//------------------------------------------------------------------------------
// Outros exercicios:
//    imprime_grafo
//    componentes_conexos
//    converte para matriz de adjacencias
//    busca elemento
//    deletar elemento na mao - assumir grafo sempre nao-direcionado - ida e volta
//    funcao para deletar elemento

