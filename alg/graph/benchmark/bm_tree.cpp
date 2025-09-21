/* Author Ricardo Fabbri rfabbri@iprj.uerj.br 2025 */
#include <benchmark/benchmark.h>
#include "tree.h"
#include <vector>
#include <algorithm>
#include <random>

static void BM_TreeInsertion(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    std::vector<int> data;
    data.reserve(state.range(0));
    std::mt19937 gen(42);
    std::uniform_int_distribution<> distrib(0, 1000000);
    for (int i = 0; i < state.range(0); ++i) {
        data.push_back(distrib(gen));
    }
    struct Node* root = NULL;
    state.ResumeTiming();

    for (int key : data) {
        root = insert(root, key);
    }
  }
  state.SetItemsProcessed(state.iterations() * state.range(0));
}

BENCHMARK(BM_TreeInsertion)->Range(8, 8<<10);

BENCHMARK_MAIN();
