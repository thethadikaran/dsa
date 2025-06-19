# create library for linked list queue
add_library(llqueue llqueue.c)

# create executable
add_executable(test_llqueue test_llqueue.c)

# link the library with test executable
target_link_libraries(test_llqueue llqueue)