add_executable(bm-tree-cmd bm_tree.cpp)
target_link_libraries(bm-tree-cmd graph benchmark::benchmark)
set_property(GLOBAL APPEND PROPERTY BENCHMARK_TARGETS bm-tree-cmd)
