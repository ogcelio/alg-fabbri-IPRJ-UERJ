#ifndef DYNAGRAPH_H
#define DYNAGRAPH_H

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct lista *lista_ptr;
typedef struct no *no_ptr;

typedef struct lista {
  no_ptr no;
  int peso;
  struct lista *next;
} lista;

typedef struct no {
  char nome[32];
  lista *conexoes;
} no;

void insere(lista **lst, no_ptr no, int peso);
void liga(no_ptr a, no_ptr b, int p);

int componente_conexo(no_ptr r, int max_conexao, no_ptr nos[], int *n_nos);
int componente_conexo_sem_maximo(no_ptr r, no_ptr nos[], int *n_nos);
void renomeia_friburgo(const no *p_petro);
void deleta_no_grafo(no_ptr r);

#ifdef __cplusplus
}
#endif

#endif // DYNAGRAPH_H
