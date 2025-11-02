#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "dynagraph.h" // Include the header for graph functions

#define MAX_NUM_NOS 1000   // maximo numero de nos para componente conexo

int main() { // monta um grafo e testa
  no nos[5]; char *nomes[5] = {"Petropolis", "Teresopolis", "Niteroi", "Rio", "Friburgo"};
  for (int i = 0; i < 5; ++i) { 
    strcpy(nos[i].nome, nomes[i]);
    nos[i].conexoes = NULL;
 }
  
 liga(nos+0, nos+1, 50);
 liga(nos+0, nos+3, 65);
 liga(nos+1, nos+3, 100);
 liga(nos+1, nos+4, 75);

 liga(nos+2, nos+3, 15);
 liga(nos+2, nos+4, 120);
 liga(nos+3, nos+4, 140);


 /*deleta_no_grafo(nos+3); // deleta Rio*/

  renomeia_friburgo(nos+0);
  no_ptr nos_componente[MAX_NUM_NOS];

  int n_nos = 0, peso_total;

  if ((peso_total = componente_conexo(nos+4, 100, nos_componente, &n_nos)) == -1 )
    return 1;
/*  if ((peso_total = componente_conexo_sem_maximo(nos+4, nos_componente, &n_nos)) == -1 ) return 1;*/

  printf("Componente de %s tem %d nos e peso total %d\n", nos[4].nome, n_nos, peso_total);
  for (int i = 0; i < n_nos; ++i){
	printf("%s\n", nos_componente[i]->nome);
	}

  // --- Adjacency Matrix Conversion ---
  printf("\n--- Teste Matriz de Adjacencia ---\n");

  int n_matrix_nos = 0;
  no_ptr matrix_nos[MAX_NUM_NOS];

  // Starting from 'nos' (Petropolis) to get the whole graph component
  int **adj_matrix = converte_para_matriz_adjacencia(nos, matrix_nos, &n_matrix_nos);

  if (adj_matrix) {
    printf("Nos na matriz (em ordem de linha/coluna): \n");
    for(int i=0; i<n_matrix_nos; ++i) {
      printf("  %d: %s\n", i, matrix_nos[i]->nome);
    }
    printf("\n");

    imprime_matriz_adjacencia(adj_matrix, n_matrix_nos);
    libera_matriz_adjacencia(adj_matrix, n_matrix_nos);
  } else {
    printf("Falha ao gerar a matriz de adjacencia.\n");
  }
  // --- Fim do Teste ---

  return 0;
}
