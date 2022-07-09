# math_test
add_executable(vec_test vec_test.cpp)
set_property(TARGET vec_test PROPERTY CXX_STANDARD 20)
target_link_libraries(vec_test gtest_main linear_algebra)
add_test(NAME vec_t COMMAND vec_test)