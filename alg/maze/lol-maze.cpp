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

no *busca(char *nome_desejado, no *inicio, char* caminho, int max_passos, int i = 0)
{
		no *atual = inicio;

		if (i == max_passos){
			cout << "Cheguei no Max de Passos" << endl;
			caminho[i] = 'x';
			return atual;
		}

		if (atual->nome != NULL){
			if (strcmp(atual->nome, nome_desejado) == 0)
			{
				caminho[i] = 'f';
				return atual;
			}
		}
		atual->visitado = true;
		if (atual->esquerda != NULL && atual->esquerda->visitado != true)
		{
			caminho[i] = 'e';
			i++;
			return busca(nome_desejado, atual->esquerda, caminho, max_passos, i);
		}
		if (atual->baixo != NULL && atual->baixo->visitado != true)
		{
			caminho[i] = 'b';
			i++;
			return busca(nome_desejado, atual->baixo, caminho, max_passos, i);
		}
		if (atual->cima != NULL && atual->cima->visitado != true)
		{
			caminho[i] = 'c';
			i++;
			return busca(nome_desejado, atual->cima, caminho, max_passos, i);
		}
		if (atual->direita != NULL && atual->direita->visitado != true)
		{
			caminho[i] = 'd';
			i++;
			return busca(nome_desejado, atual->direita, caminho, max_passos, i);
		}
		cout << "retornei null" << endl;
		return NULL;
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






