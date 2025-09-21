#include <iostream>
#include <string>
#include <limits>
#include <string.h>
#include <stdio.h> // For perror
#include <stdlib.h> // For malloc/free
#include "linked_list.h"

int
main()
{
    char x; //choice
    int index;

    singly_list_item *head = (singly_list_item*) (malloc(sizeof(singly_list_item)));
    if (head == NULL) {
        perror("Failed to allocate memory for list head");
        return 1;
    }
    head->prox = NULL;

    std::cout << "Hi, select one of the following keys:\n" << std::endl;

    while (true) {
        std::cout << "\n[P] Print || [I] Insert || [D] Delete || [S] Sum || [R] Sum Recursive || [E] Exit\n" << std::endl;

        std::cin >> x;

        if (x == 'p' or x == 'P'){
            print_list(head);
        }
        else if (x == 'i' or x == 'I'){
            // cleaning the buffer
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            char *value = (char*) (malloc(sizeof(char) * 256));
            if (value == NULL) {
                perror("Failed to allocate memory for input string");
                continue; // Continue to next loop iteration
            }

            std::cout << "Write the string to add in the linked list:\n" << std::endl;

            if (fgets(value, 256, stdin) != NULL) {
                value[strcspn(value, "\n")] = '\0';
            } else {
                free(value); // Don't leak if fgets fails
                continue;
            }

            std::cout << "Now, write the index to insert the element:\n" << std::endl;
            std::cin >> index;

            if (std::cin.fail()) {
                std::cout << "Invalid index. Please enter a number.\n" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                free(value); // Free the allocated string before continuing
                continue;
            }

            add_item(head, index, value);
        }
        else if (x == 'd' or x == 'D'){
            std::cout << "Write the index of the item to delete:\n" << std::endl;
            std::cin >> index;
            
            if (std::cin.fail()) {
                std::cout << "Invalid index. Please enter a number.\n" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            remove_item(head, index);
        }
	else if (x == 's' or x == 'S'){
	    std::cout << "Total Sum:" << sum(head);
	}
	else if (x == 'r' or x == 'R'){
	    int total = 0;
	    
	    std::cout << "Total Sum:" << sum_recursive(head);
	}
        else if (x == 'e' or x == 'E'){
            std::cout << "Exiting...\n" << std::endl;
            break;
        }
        else{
            std::cout << "Pick one of the options listed.\n" << std::endl;
        }
    }

    free_list(head); // Deallocate the entire list

    return 0;
}
