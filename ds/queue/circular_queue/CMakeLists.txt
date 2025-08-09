# create library for linked list queue
add_library(cqueue cqueue.c)

# create executable
add_executable(test_cqueue test_cqueue.c)

# link the library with test executable
target_link_libraries(test_cqueue cqueue)