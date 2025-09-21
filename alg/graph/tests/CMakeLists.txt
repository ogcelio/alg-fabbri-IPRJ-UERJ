include(GoogleTest)

add_executable(run-graph-tests test-tree.cpp)
target_link_libraries(run-graph-tests PRIVATE graph GTest::gtest_main GTest::gtest)

gtest_discover_tests(run-graph-tests)
