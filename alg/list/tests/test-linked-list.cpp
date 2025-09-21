/* R. Fabbri, 2025 */
#include <gtest/gtest.h>
#include <string.h> // For memcmp
#include <stdio.h>

#include "linked_list.h"
#include "doubly_linked_list.h"
#include "circular_linked_list.h"

// Test fixture for linked_list
class LinkedListTest : public ::testing::Test {
protected:
    singly_list_item* head;

    void SetUp() override {
        head = (singly_list_item*)malloc(sizeof(singly_list_item));
        head->prox = NULL;
    }

    void TearDown() override {
        free_list(head);
    }

    // Helper to get the size of the list
    int get_list_size(singly_list_item* h) {
        int count = 0;
        singly_list_item* current = h->prox;
        while (current != NULL) {
            count++;
            current = current->prox;
        }
        return count;
    }
};

TEST_F(LinkedListTest, AddAndRemoveItems) {
    char* val1 = strdup("first");
    char* val2 = strdup("second");
    char* val3 = strdup("third");

    add_item(head, 1, val1);
    ASSERT_EQ(get_list_size(head), 1);

    add_item(head, 2, val2);
    ASSERT_EQ(get_list_size(head), 2);

    add_item(head, 1, val3);
    ASSERT_EQ(get_list_size(head), 3);

    // List should be: third -> first -> second
    ASSERT_STREQ(head->prox->string, "third");
    ASSERT_STREQ(head->prox->prox->string, "first");
    ASSERT_STREQ(head->prox->prox->prox->string, "second");

    remove_item(head, 2); // Remove 'first'
    ASSERT_EQ(get_list_size(head), 2);
    ASSERT_STREQ(head->prox->string, "third");
    ASSERT_STREQ(head->prox->prox->string, "second");

    remove_item(head, 1); // Remove 'third'
    ASSERT_EQ(get_list_size(head), 1);
    ASSERT_STREQ(head->prox->string, "second");

    remove_item(head, 1); // Remove 'second'
    ASSERT_EQ(get_list_size(head), 0);
    ASSERT_EQ(head->prox, nullptr);
}

TEST_F(LinkedListTest, SumFunction) {
    char* val1 = strdup("a");
    char* val2 = strdup("bb");
    char* val3 = strdup("ccc");

    add_item(head, 1, val1);
    add_item(head, 2, val2);
    add_item(head, 3, val3);

    ASSERT_EQ(sum(head), 6); // 1 + 2 + 3
}

TEST_F(LinkedListTest, SumRecursiveFunction) {
    char* val1 = strdup("a");
    char* val2 = strdup("bb");
    char* val3 = strdup("ccc");

    add_item(head, 1, val1);
    add_item(head, 2, val2);
    add_item(head, 3, val3);

    ASSERT_EQ(sum_recursive(head), 6); // 1 + 2 + 3
}

// Test fixture for doubly_linked_list
class DoublyLinkedListTest : public ::testing::Test {
protected:
    doubly_list_item* head;

    void SetUp() override {
        head = (doubly_list_item*)malloc(sizeof(doubly_list_item));
        head->prox = NULL;
        head->prev = NULL;
    }

    void TearDown() override {
        free_list(head);
    }

    // Helper to get the size of the list
    int get_list_size(doubly_list_item* h) {
        int count = 0;
        doubly_list_item* current = h->prox;
        while (current != NULL) {
            count++;
            current = current->prox;
        }
        return count;
    }
};

TEST_F(DoublyLinkedListTest, AddAndRemoveItems) {
    char* val1 = strdup("first");
    char* val2 = strdup("second");
    char* val3 = strdup("third");

    add_item(head, 1, val1);
    ASSERT_EQ(get_list_size(head), 1);

    add_item(head, 2, val2);
    ASSERT_EQ(get_list_size(head), 2);

    add_item(head, 1, val3);
    ASSERT_EQ(get_list_size(head), 3);

    // List should be: third -> first -> second
    ASSERT_STREQ(head->prox->string, "third");
    ASSERT_STREQ(head->prox->prox->string, "first");
    ASSERT_STREQ(head->prox->prox->prox->string, "second");

    remove_item(head, 2); // Remove 'first'
    ASSERT_EQ(get_list_size(head), 2);
    ASSERT_STREQ(head->prox->string, "third");
    ASSERT_STREQ(head->prox->prox->string, "second");

    remove_item(head, 1); // Remove 'third'
    ASSERT_EQ(get_list_size(head), 1);
    ASSERT_STREQ(head->prox->string, "second");

    remove_item(head, 1); // Remove 'second'
    ASSERT_EQ(get_list_size(head), 0);
    ASSERT_EQ(head->prox, nullptr);
}

// Test fixture for circular_linked_list
class CircularLinkedListTest : public ::testing::Test {
protected:
    circular_list_item* head;

    void SetUp() override {
        head = (circular_list_item*)malloc(sizeof(circular_list_item));
        head->prox = head; // Circular list head points to itself when empty
    }

    void TearDown() override {
        // Custom free_list for circular linked list
        circular_list_item *actual = head->prox;
        circular_list_item *tb_removed = NULL;
        while (actual != head) {
            tb_removed = actual;
            actual = actual->prox;
            free(tb_removed->string);
            free(tb_removed);
        }
        free(head);
    }

    // Helper to get the size of the list
    int get_list_size(circular_list_item* h) {
        int count = 0;
        circular_list_item* current = h->prox;
        while (current != h) {
            count++;
            current = current->prox;
        }
        return count;
    }
};

TEST_F(CircularLinkedListTest, AddAndRemoveItems) {
    char* val1 = strdup("first");
    char* val2 = strdup("second");
    char* val3 = strdup("third");

    add_item(head, 1, val1);
    ASSERT_EQ(get_list_size(head), 1);

    add_item(head, 2, val2);
    ASSERT_EQ(get_list_size(head), 2);

    add_item(head, 1, val3);
    ASSERT_EQ(get_list_size(head), 3);

    // List should be: third -> first -> second
    ASSERT_STREQ(head->prox->string, "third");
    ASSERT_STREQ(head->prox->prox->string, "first");
    ASSERT_STREQ(head->prox->prox->prox->string, "second");

    remove_item(head, 2); // Remove 'first'
    ASSERT_EQ(get_list_size(head), 2);
    ASSERT_STREQ(head->prox->string, "third");
    ASSERT_STREQ(head->prox->prox->string, "second");

    remove_item(head, 1); // Remove 'third'
    ASSERT_EQ(get_list_size(head), 1);
    ASSERT_STREQ(head->prox->string, "second");

    remove_item(head, 1); // Remove 'second'
    ASSERT_EQ(get_list_size(head), 0);
    ASSERT_EQ(head->prox, head);
}
