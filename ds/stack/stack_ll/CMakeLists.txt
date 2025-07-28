# create library for single linked list
add_library(stack_ll stack_ll.c)

# create executable
add_executable(test_stack_ll test_stack_ll.c)

# link the library with test executable
target_link_libraries(test_stack_ll stack_ll)