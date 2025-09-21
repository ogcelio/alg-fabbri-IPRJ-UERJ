/* R. Fabbri, 2025 */
#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

struct doubly_linked_list_item {
	char *string;
	struct doubly_linked_list_item *prox;
    struct doubly_linked_list_item *prev;
};

typedef struct doubly_linked_list_item doubly_list_item;

void free_list(doubly_list_item* head);
void remove_item(doubly_list_item* head, int index);
void add_item(doubly_list_item* head, int index, char* value);
void print_list(doubly_list_item* head);

#endif /* DOUBLY_LINKED_LIST_H */
