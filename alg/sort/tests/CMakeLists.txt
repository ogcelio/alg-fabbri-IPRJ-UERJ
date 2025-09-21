include(GoogleTest)

add_executable(run-sort-tests test-sort-char.cpp)
target_link_libraries(run-sort-tests PRIVATE sort GTest::gtest_main GTest::gtest)

# The gtest_discover_tests() function automatically finds and registers tests
# with CTest. It should be called after all test executables have been defined.
gtest_discover_tests(run-sort-tests)
