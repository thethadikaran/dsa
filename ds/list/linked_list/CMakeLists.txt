# create library for single linked list
add_library(linked_list linked_list.c)

# create executable
add_executable(test_linked_list test_linked_list.c)

# link the library with test executable
target_link_libraries(test_linked_list linked_list)