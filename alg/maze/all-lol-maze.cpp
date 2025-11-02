#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

struct no {
	char *nome; 
	no *esquerda;
	no *baixo;
	no *cima;
	no *direita;
	bool visitado;
};

struct linked_track{
	char* track;
	linked_track *next;
};

typedef struct linked_track* t;

no *busca(char *nome_desejado, no *inicio, t head_caminho, int i = 0)
{
	int j;
	no *atual = inicio;

	atual->visitado = true;
	for (j = 0; j < 4; j++) {
		if (atual->nome != NULL){
			t t_atual = head_caminho->next;
			if (strcmp(atual->nome, nome_desejado) == 0)
			{
				t_atual->track[i] = 'f';
				continue;
				return atual;
			}
		}
	
		if (atual->esquerda != NULL && atual->esquerda->visitado != true)
		{
			t_atual->track[i]  = 'e';
			i++;
			return busca(nome_desejado, atual->esquerda, caminho, max_passos, i);
		}

		if (atual->baixo != NULL && atual->baixo->visitado != true)
		{
			t_atual->track[i]  = 'b';
			i++;
			return busca(nome_desejado, atual->baixo, caminho, max_passos, i);
		}
		if (atual->cima != NULL && atual->cima->visitado != true)
		{
			t_atual->track[i]  = 'c';
			i++;
			return busca(nome_desejado, atual->cima, caminho, max_passos, i);
		}
		if (atual->direita != NULL && atual->direita->visitado != true)
		{
			t_atual->track[i]  = 'd';
			i++;
			return busca(nome_desejado, atual->direita, caminho, max_passos, i);
		}
	}
}	

void
inserir_nome(no* node, char* name, int size)
{
	node->nome = (char*) (malloc(sizeof(size + 1)));
	strcpy(node->nome, name);
}

int
main()
{
	no *inicio = (no *) (malloc(sizeof(no)));

	no *bisecao = (no *) (malloc(sizeof(no)));
	inicio->direita = bisecao;

	no *moedas = (no *) (malloc(sizeof(no)));
	bisecao->cima = moedas;
	bisecao->esquerda = inicio;
	inserir_nome(moedas, "moedas", 6);

	no *vazio = (no *) (malloc(sizeof(no)));
	bisecao->baixo = vazio;
	moedas->baixo = vazio;
	vazio->cima = moedas;

	no *boss = (no *) (malloc(sizeof(no)));
	boss->cima = moedas;
	boss->baixo = vazio;
	vazio->direita = boss;
	moedas->direita = boss;
	inserir_nome(boss, "boss", 4);

	no *fim = (no *) (malloc(sizeof(no)));
	fim->esquerda = boss;
	boss->direita = fim;
	inserir_nome(fim, "game over", 9);

	no *resultado = (no *) (malloc(sizeof(no)));
	inserir_nome(resultado, " ", 9);
	
	unsigned int max_passos = 10;
	char *caminho = (char *) (malloc(max_passos+1));
	resultado = busca("game over", inicio, caminho, max_passos);
	
	if (resultado->nome != NULL){
		cout << "Nome no Nodo: " << resultado->nome << endl;
	}

	cout << "Caminho: " << caminho << endl;
	cout << "Numero de Passos: " << strlen(caminho) - 1 << endl; 

	return 0;
}






