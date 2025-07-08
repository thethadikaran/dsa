# create library for single linked list
add_library(dlinked_list dlinked_list.c)

# create executable
add_executable(test_dlinked_list test_dlinked_list.c)

# link the library with test executable
target_link_libraries(test_dlinked_list dlinked_list)