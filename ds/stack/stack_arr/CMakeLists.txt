# create library for single linked list
add_library(stack_arr stack_arr.c)

# create executable
add_executable(test_stack_arr test_stack_arr.c)

# link the library with test executable
target_link_libraries(test_stack_arr stack_arr)