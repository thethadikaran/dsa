# create library for single linked list
add_library(llstack llstack.c)

# create executable
add_executable(test_llstack test_llstack.c)

# link the library with test executable
target_link_libraries(test_llstack llstack)