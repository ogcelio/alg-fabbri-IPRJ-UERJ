#include <benchmark/benchmark.h>
#include "../sort-char.h"
#include <cstring>

static void BM_SortChar(benchmark::State& state) {
  char str[] = "thequickbrownfoxjumpsoverthelazydog";
  for (auto _ : state) {
    sort_char(str);
  }
}
BENCHMARK(BM_SortChar);

BENCHMARK_MAIN();
