#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONEXOES 100
#define MAX_CARACTERES 32
#define NUM_NOS 5

typedef struct no *no_ptr;
typedef struct arestas *a_ptr;

typedef struct arestas {
	int peso;
	no_ptr aponta;	
} arestas;

typedef struct no {
	char nome[MAX_CARACTERES];
	arestas conexoes[MAX_CONEXOES];
	int num_conexoes;
	int id;
} no;

void
liga(no_ptr no_partida, no_ptr no_chegada, int peso)
{
	if (no_partida->num_conexoes < MAX_CONEXOES && no_chegada->num_conexoes < MAX_CONEXOES){
		// Colocando conexao no No de partida
		int index_partida = no_partida->num_conexoes;
		no_partida->conexoes[index_partida].aponta = no_chegada;
		no_partida->conexoes[index_partida].peso = peso;
		no_partida->num_conexoes++;
	
		// Colocando conexao no No de chegada
		int index_chegada = no_chegada->num_conexoes;
		no_chegada->conexoes[index_chegada].aponta = no_partida;
		no_chegada->conexoes[index_chegada].peso = peso;
		no_chegada->num_conexoes++;
	}
	else{
		printf("voce nao pode adicionar mais conexoes nesses nos.");
	}
}

no_ptr
criar_no(char nome[MAX_CARACTERES], int id)
{
	no_ptr no_criado = (no_ptr) malloc(sizeof(no));
	strcpy(no_criado->nome, nome);
	no_criado->num_conexoes = 0;
	no_criado->id = id;

	return no_criado;
}

void
montar_matriz_adjacencia(int matriz_adj[NUM_NOS][NUM_NOS], no_ptr lista_nos[NUM_NOS])
{
	for (int i=0; i < NUM_NOS; i++)
	{
		for (int j=0; j < NUM_NOS; j++) 
		{
			matriz_adj[i][j] = 0;
		}
	}
	
	int id;

    	for (int i = 0; i < NUM_NOS; i++) 
	{
        	no_ptr no_origem = lista_nos[i];
        
        	for (int k = 0; k < no_origem->num_conexoes; k++)
		{
            		no_ptr no_destino = no_origem->conexoes[k].aponta;
            		int peso = no_origem->conexoes[k].peso;
            
            		id = no_destino->id;

            		matriz_adj[i][id] = peso;
        	}
    	}
}

void
print_matriz(int matriz_adj[NUM_NOS][NUM_NOS], no_ptr lista_nos[NUM_NOS])
{
	printf("\n--- Matriz de Adjacência ---\n\n");
    
    	// Cabeçalho (Colunas)
    	printf("        "); // Espaço
    	for (int j = 0; j < NUM_NOS; j++) 
	{
        	printf("%.3s. ", lista_nos[j]->nome); // Imprime as 3 primeiras letras
    	}
    	printf("\n        ");
    	for (int j = 0; j < NUM_NOS; j++)
	{
        	printf("-----");
    	}
    	printf("\n");

    	// Linhas
	for (int i = 0; i < NUM_NOS; i++) 
	{
        	printf("%.3s. | ", lista_nos[i]->nome); // Cabeçalho da Linha
        	for (int j = 0; j < NUM_NOS; j++) 
		{
            		printf("%-4d ", matriz_adj[i][j]); // Imprime com 4 espaços
        	}
        	printf("\n");
    	}
}

int
main()
{
	no_ptr pet = criar_no("Petropolis", 0);
	no_ptr tere = criar_no("Teresopolis", 1);
	no_ptr nit = criar_no("Niteroi", 2);
	no_ptr rio = criar_no("Rio", 3);
	no_ptr fri = criar_no("Friburgo", 4);
	
	liga(nit, rio, 15);
	liga(nit, fri, 120);

	liga(rio, fri, 140);
	liga(rio, tere, 100);
	liga(rio, pet, 65);
	
	liga(pet, tere, 50);
	liga(tere, fri, 75);

	no_ptr lista_nos[NUM_NOS] = {pet, tere, nit, rio, fri};
	
	int matriz_adj[NUM_NOS][NUM_NOS];
	
	montar_matriz_adjacencia(matriz_adj, lista_nos);

	print_matriz(matriz_adj, lista_nos);

	return 0;
}
