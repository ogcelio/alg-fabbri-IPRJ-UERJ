/* R. Fabbri, 2025 */
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

struct singly_linked_list {
	char *string;
	struct singly_linked_list *prox;
};

typedef struct singly_linked_list singly_list_item;

void free_list(singly_list_item* head);
void remove_item(singly_list_item* head, int index);
void add_item(singly_list_item* head, int index, char* value);
void print_list(singly_list_item* head);
int sum(singly_list_item* head);
int sum_recursive(singly_list_item* head);

#endif /* LINKED_LIST_H */
