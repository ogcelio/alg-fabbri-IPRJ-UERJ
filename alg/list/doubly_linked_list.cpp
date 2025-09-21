#include "doubly_linked_list.h"
#include <iostream>
#include <string>
#include <limits>
#include <string.h>
#include <stdio.h> // For perror
#include <stdlib.h> // For malloc/free



void
free_list(doubly_list_item* head)
{
    doubly_list_item *actual = head->prox; // Start with the first actual item
    doubly_list_item *tb_removed = NULL;
    while (actual != NULL) {
        tb_removed = actual;
        actual = actual->prox;
        free(tb_removed->string);
        free(tb_removed);
    }
    // Finally, free the head dummy node itself
    free(head);
}

void
remove_item(doubly_list_item* head, int index)
{
    if (index <= 0) {
        std::cout << "You can\'t remove an item with an invalid index.\n" << std::endl;
        return;
    }

    doubly_list_item *actual = head;

    int i = 0;

    while ((i < (index - 1)) && (actual->prox != NULL)){
        actual = actual->prox;
        i++;
    }

    if (actual->prox == NULL){
        std::cout << "You can\'t remove an item that doesn\'t exist.\n" << std::endl;
        return;
    }

    doubly_list_item *tb_removed = actual->prox;

    actual->prox = tb_removed->prox;
    if (tb_removed->prox != NULL) {
        tb_removed->prox->prev = actual;
    }

    free(tb_removed->string);
    free(tb_removed);
}

void
add_item(doubly_list_item* head, int index, char* value)
{
    if (index <= 0) {
        std::cout << "Cannot insert at an invalid index. Please use an index of 1 or greater.\n" << std::endl;
        free(value); // Prevent memory leak if index is invalid
        return;
    }

    doubly_list_item *novo = (doubly_list_item*) (malloc(sizeof(doubly_list_item)));
    if (novo == NULL) {
        perror("Failed to allocate memory for new item");
        free(value); // Prevent memory leak on malloc failure
        return;
    }

    novo->string = value;

    doubly_list_item *actual = head;

    int i = 1;

    while ((i < index) && (actual->prox != NULL)){
        actual = actual->prox;
        i++;
    }

    novo->prox = actual->prox;
    novo->prev = actual;
    if (actual->prox != NULL) {
        actual->prox->prev = novo;
    }
    actual->prox = novo;
}

void
print_list(doubly_list_item* head)
{
    doubly_list_item *actual = head->prox;

    if (actual == NULL){
        std::cout << "The list is empty.\n" << std::endl;
        return;
    }

    int i = 1;

    while (actual != NULL){
        printf("Item: %d -- Value: %s\n", i, actual->string);
        actual = actual->prox;
        i++;
    }
    std::cout << std::endl; // For better spacing
}

