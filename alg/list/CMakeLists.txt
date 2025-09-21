add_library(list 
  linked_list.cpp
  doubly_linked_list.cpp
  circular_linked_list.cpp
)

target_include_directories(list PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(cmd)

if (alg_BUILD_TESTS)
  add_subdirectory(tests)
endif(alg_BUILD_TESTS)

if (alg_BUILD_BENCHMARKS)
  add_subdirectory(benchmark)
endif(alg_BUILD_BENCHMARKS)
