# create library for single linked list
add_library(astack astack.c)

# create executable
add_executable(test_astack test_astack.c)

# link the library with test executable
target_link_libraries(test_astack astack)