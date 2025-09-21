add_executable(bm-sort-char bm_sort-char.cpp)
target_link_libraries(bm-sort-char sort benchmark::benchmark)
set_property(GLOBAL APPEND PROPERTY BENCHMARK_TARGETS bm-sort-char)
