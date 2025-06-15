# create library for single linked list
add_library(clinked_list clinked_list.c)

# create executable
add_executable(test_clinked_list test_clinked_list.c)

# link the library with test executable
target_link_libraries(test_clinked_list clinked_list)