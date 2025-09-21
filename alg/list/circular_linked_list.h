/* R. Fabbri, 2025 */
#ifndef CIRCULAR_LINKED_LIST_H
#define CIRCULAR_LINKED_LIST_H

struct circular_linked_list_item {
	char *string;
	struct circular_linked_list_item *prox;
};

typedef struct circular_linked_list_item circular_list_item;

void free_list(circular_list_item* head);
void remove_item(circular_list_item* head, int index);
void add_item(circular_list_item* head, int index, char* value);
void print_list(circular_list_item* head);

#endif /* CIRCULAR_LINKED_LIST_H */
