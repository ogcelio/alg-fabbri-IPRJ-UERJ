/* Author Ricardo Fabbri rfabbri@iprj.uerj.br 2025 */
#include <benchmark/benchmark.h>
#include "linked_list.h"
#include "doubly_linked_list.h"
#include "circular_linked_list.h"
#include <vector>
#include <string>
#include <random>
#include <cstring> // For strdup

// Helper function to create a list of a given size
singly_list_item* create_linked_list(int size) {
    singly_list_item* head = (singly_list_item*)malloc(sizeof(singly_list_item));
    head->prox = NULL;
    for (int i = 0; i < size; ++i) {
        char* val = strdup(std::to_string(i).c_str());
        add_item(head, i + 1, val);
    }
    return head;
}

// Helper function to create a doubly linked list of a given size
doubly_list_item* create_doubly_linked_list(int size) {
    doubly_list_item* head = (doubly_list_item*)malloc(sizeof(doubly_list_item));
    head->prox = NULL;
    head->prev = NULL;
    for (int i = 0; i < size; ++i) {
        char* val = strdup(std::to_string(i).c_str());
        add_item(head, i + 1, val);
    }
    return head;
}

// Helper function to create a circular linked list of a given size
circular_list_item* create_circular_linked_list(int size) {
    circular_list_item* head = (circular_list_item*)malloc(sizeof(circular_list_item));
    head->prox = head;
    for (int i = 0; i < size; ++i) {
        char* val = strdup(std::to_string(i).c_str());
        add_item(head, i + 1, val);
    }
    return head;
}

// Benchmark for singly linked list add_item
static void BM_LinkedList_AddItem(benchmark::State& state) {
    int size = state.range(0);
    for (auto _ : state) {
        state.PauseTiming();
        singly_list_item* head = (singly_list_item*)malloc(sizeof(singly_list_item));
        head->prox = NULL;
        state.ResumeTiming();
        for (int i = 0; i < size; ++i) {
            char* val = strdup(std::to_string(i).c_str());
            add_item(head, i + 1, val);
        }
        state.PauseTiming();
        free_list(head);
        state.ResumeTiming();
    }
    state.SetItemsProcessed(state.iterations() * size);
}
BENCHMARK(BM_LinkedList_AddItem)->Range(1, 1024);

// Benchmark for singly linked list remove_item
static void BM_LinkedList_RemoveItem(benchmark::State& state) {
    int size = state.range(0);
    for (auto _ : state) {
        state.PauseTiming();
        singly_list_item* head = create_linked_list(size);
        state.ResumeTiming();
        for (int i = 0; i < size; ++i) {
            remove_item(head, 1);
        }
        state.PauseTiming();
        free(head); // Only head remains after all removals
        state.ResumeTiming();
    }
    state.SetItemsProcessed(state.iterations() * size);
}
BENCHMARK(BM_LinkedList_RemoveItem)->Range(1, 1024);

// Benchmark for doubly linked list add_item
static void BM_DoublyLinkedList_AddItem(benchmark::State& state) {
    int size = state.range(0);
    for (auto _ : state) {
        state.PauseTiming();
        doubly_list_item* head = (doubly_list_item*)malloc(sizeof(doubly_list_item));
        head->prox = NULL;
        head->prev = NULL;
        state.ResumeTiming();
        for (int i = 0; i < size; ++i) {
            char* val = strdup(std::to_string(i).c_str());
            add_item(head, i + 1, val);
        }
        state.PauseTiming();
        free_list(head);
        state.ResumeTiming();
    }
    state.SetItemsProcessed(state.iterations() * size);
}
BENCHMARK(BM_DoublyLinkedList_AddItem)->Range(1, 1024);

// Benchmark for doubly linked list remove_item
static void BM_DoublyLinkedList_RemoveItem(benchmark::State& state) {
    int size = state.range(0);
    for (auto _ : state) {
        state.PauseTiming();
        doubly_list_item* head = create_doubly_linked_list(size);
        state.ResumeTiming();
        for (int i = 0; i < size; ++i) {
            remove_item(head, 1);
        }
        state.PauseTiming();
        free(head); // Only head remains after all removals
        state.ResumeTiming();
    }
    state.SetItemsProcessed(state.iterations() * size);
}
BENCHMARK(BM_DoublyLinkedList_RemoveItem)->Range(1, 1024);

// Benchmark for circular linked list add_item
static void BM_CircularLinkedList_AddItem(benchmark::State& state) {
    int size = state.range(0);
    for (auto _ : state) {
        state.PauseTiming();
        circular_list_item* head = (circular_list_item*)malloc(sizeof(circular_list_item));
        head->prox = head;
        state.ResumeTiming();
        for (int i = 0; i < size; ++i) {
            char* val = strdup(std::to_string(i).c_str());
            add_item(head, i + 1, val);
        }
        state.PauseTiming();
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
        state.ResumeTiming();
    }
    state.SetItemsProcessed(state.iterations() * size);
}
BENCHMARK(BM_CircularLinkedList_AddItem)->Range(1, 1024);

// Benchmark for circular linked list remove_item
static void BM_CircularLinkedList_RemoveItem(benchmark::State& state) {
    int size = state.range(0);
    for (auto _ : state) {
        state.PauseTiming();
        circular_list_item* head = create_circular_linked_list(size);
        state.ResumeTiming();
        for (int i = 0; i < size; ++i) {
            remove_item(head, 1);
        }
        state.PauseTiming();
        // Only head remains after all removals, but it's a circular list
        // The head itself is freed in the next iteration's setup
        // For circular list, after all items are removed, head->prox should point to head
        if (head->prox != head) {
            // This should not happen if all items are removed correctly
            // For safety, free remaining items if any
            circular_list_item *actual = head->prox;
            circular_list_item *tb_removed = NULL;
            while (actual != head) {
                tb_removed = actual;
                actual = actual->prox;
                free(tb_removed->string);
                free(tb_removed);
            }
        }
        free(head);
        state.ResumeTiming();
    }
    state.SetItemsProcessed(state.iterations() * size);
}
BENCHMARK(BM_CircularLinkedList_RemoveItem)->Range(1, 1024);

BENCHMARK_MAIN();