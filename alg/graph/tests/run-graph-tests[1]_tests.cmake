add_test([=[TreeTest.BasicInsertion]=]  /home/synthyaga/.a/alg-fabbri-IPRJ-UERJ/alg/graph/tests/run-graph-tests [==[--gtest_filter=TreeTest.BasicInsertion]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TreeTest.BasicInsertion]=]  PROPERTIES WORKING_DIRECTORY /home/synthyaga/.a/alg-fabbri-IPRJ-UERJ/alg/graph/tests SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  run-graph-tests_TESTS TreeTest.BasicInsertion)
