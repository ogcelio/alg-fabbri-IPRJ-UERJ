#include <benchmark/benchmark.h>
#include "dynagraph.h"
#include <string.h>

static void BM_GraphCreation(benchmark::State& state) {
  for (auto _ : state) {
    no nos[2];
    strcpy(nos[0].nome, "A");
    nos[0].conexoes = NULL;
    strcpy(nos[1].nome, "B");
    nos[1].conexoes = NULL;

    liga(nos, nos + 1, 10);
  }
}
BENCHMARK(BM_GraphCreation);

BENCHMARK_MAIN();
