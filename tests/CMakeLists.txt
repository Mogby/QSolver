add_executable(run_tests tests.cpp)

add_test(tests ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/run_tests)
