add_test([=[GraphTest.BasicAssertions]=]  /home/synthyaga/.a/alg-fabbri-IPRJ-UERJ/alg/graph/tests/run-graph-tests [==[--gtest_filter=GraphTest.BasicAssertions]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[GraphTest.BasicAssertions]=]  PROPERTIES WORKING_DIRECTORY /home/synthyaga/.a/alg-fabbri-IPRJ-UERJ/alg/graph/tests SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  run-graph-tests_TESTS GraphTest.BasicAssertions)
