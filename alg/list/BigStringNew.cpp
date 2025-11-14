#include <iostream>
#include <string.h>
#include <stdlib.h>

using namespace std;

#define TAMANHO_MAX 64

class BigString
{
public:
  char string[TAMANHO_MAX];
  BigString *prox;

  void define_name(char *name)
  {
    strcpy(string, name);
  }
};

// Conta quantas listas encadeadas existem, a partir da head
int
get_list_size(BigString *head)
{
  int count = 0;
  for (BigString *current = head; current != NULL; current = current->prox)
  {
    count++;
  }
  return count;
}

// cria a lista cumulativa de indices, a partir da head
void
build_cumulative_sizes(BigString *head, unsigned int *cumulative_sizes, int n)
{
  BigString *current = head;
  unsigned int total_size = 0;
  for (int i = 0; i < n; i++)
  {
    total_size += strlen(current->string);
    cumulative_sizes[i] = total_size;
    current = current->prox;
  }
}

int
binary_search_cumulative(unsigned int *arr, int n, int target_index)
{
  int low = 0;
  int high = n - 1;
  int result = -1;

  while (low <= high)
  {
    int mid = low + (high - low) / 2;
    if (target_index < arr[mid])
    {
      result = mid;
      high = mid - 1;
    }
    else
    {
      low = mid + 1;
    }
  }
  return result;
}

void
find_index_bs(int index, BigString *s)
{
  if (!s)
    return;

  int n = get_list_size(s);
  if (n == 0)
    return;

  unsigned int *cumulative_sizes = (unsigned int *)malloc(n * sizeof(unsigned int));
  if (!cumulative_sizes)
  {
    perror("Failed to allocate memory for cumulative_sizes");
    return;
  }

  build_cumulative_sizes(s, cumulative_sizes, n);

  if (index < 0 || index >= cumulative_sizes[n - 1])
  {
    cout << "Index out of bounds" << endl;
    free(cumulative_sizes);
    return;
  }

  int node_index = binary_search_cumulative(cumulative_sizes, n, index);

  BigString *target_node = s;
  for (int i = 0; i < node_index; i++)
  {
    target_node = target_node->prox;
  }

  unsigned int local_index = index;
  if (node_index > 0)
  {
    local_index -= cumulative_sizes[node_index - 1];
  }

  cout << target_node->string[local_index] << endl;

  free(cumulative_sizes);
}

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
insert_name(int index, char name[TAMANHO_MAX], BigString *s)
{
  // INICIO DA BUSCA BINARIA
  if (!s)
    return -1;

  int n = get_list_size(s);
  if (n == 0)
    return -1;

  unsigned int *cumulative_sizes = (unsigned int *)malloc(n * sizeof(unsigned int));
  if (!cumulative_sizes)
  {
    perror("Failed to allocate memory for cumulative_sizes");
    return -1;
  }

  build_cumulative_sizes(s, cumulative_sizes, n);

  if (index < 0 || index >= cumulative_sizes[n - 1])
  {
    cout << "Index out of bounds" << endl;
    free(cumulative_sizes);
    return -1;
  }

  int node_index = binary_search_cumulative(cumulative_sizes, n, index);

  BigString *target_node = s;
  for (int i = 0; i < node_index; i++)
  {
    target_node = target_node->prox;
  }

  unsigned int local_index = index;
  if (node_index > 0)
  {
    local_index -= cumulative_sizes[node_index - 1];
  }

  free(cumulative_sizes);
  // FIM DA BUSCA BINARIA

  char *string = target_node->string;

  if ((strlen(string) + strlen(name)+1) > TAMANHO_MAX)
    return -1;
  
  unsigned int final_size = strlen(string) - local_index;

  char start[local_index+1];
  char end[final_size+1];

  strncpy(start, string, local_index);
  strncpy(end, string + local_index, final_size);

  start[local_index] = '\0';
  end[final_size] = '\0';

  char result[TAMANHO_MAX];

  strcpy(result, start);

  strcat(result, name);

  strcat(result, end);

  target_node->define_name(result);

  return 0;
}

int
main()
{
  BigString *s = (BigString *)malloc(sizeof(BigString));
  s->define_name("joao");

  BigString *p = (BigString *)malloc(sizeof(BigString));
  p->define_name("celio");
  s->prox = p;

  BigString *q = (BigString *)malloc(sizeof(BigString));
  q->define_name("come");
  p->prox = q;

  BigString *r = (BigString *)malloc(sizeof(BigString));
  r->define_name("pao de banana");
  q->prox = r;
  r->prox = NULL;

  // joao (4) celio (5) come (4) pao de banana (13)
  // cumulative: 4, 9, 13, 18
  // index 8 -> 'o' in "celio"

  cout << "String antiga: " << q->string << endl;

  insert_name(13, ".nomeio.", s);

  cout << "String nova: " << r->string << endl;
  
  free(s);
  free(p);
  free(q);
  free(r);

  return 0;
}
