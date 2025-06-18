# create library for single linked list
add_library(hlinked_list hlinked_list.c)

# create executable
add_executable(test_hlinked_list test_hlinked_list.c)

# link the library with test executable
target_link_libraries(test_hlinked_list hlinked_list)