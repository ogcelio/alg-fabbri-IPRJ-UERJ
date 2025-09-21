add_test([=[SortCharTest.Simple]=]  /home/synthyaga/.a/alg-fabbri-IPRJ-UERJ/alg/sort/tests/run-sort-tests [==[--gtest_filter=SortCharTest.Simple]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SortCharTest.Simple]=]  PROPERTIES WORKING_DIRECTORY /home/synthyaga/.a/alg-fabbri-IPRJ-UERJ/alg/sort/tests SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  run-sort-tests_TESTS SortCharTest.Simple)
