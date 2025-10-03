#include <iostream>
using namespace std;
#include <string.h>

class BigString 
{
	public:
		char *string;
		BigString *prox;
		unsigned int item_size = strlen(string);
		
		void define_name(char *name)
		{
			string = name;
			item_size = strlen(string);
		};

};

void
print_index(int index, BigString *s)
{
	char* string = s->string;
	int i = 0, j = 0;

	for (i = 0, j = 0; i < index; i++){
		if (string[i] == '\0'){
			j=0;
			string = s->prox->string;	
		}
		j++;
	}
	cout << string[j] << endl;
}

int
main()
{
	BigString *s = (BigString*) (malloc(sizeof(BigString)));

	s->define_name("joao");

	BigString *p = (BigString*) (malloc(sizeof(BigString)));
	
	p->define_name("celio");
	s->prox = p;
	
	print_index(8, s);

	return 0;
} 


