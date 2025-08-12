# create library for linked list queue
add_library(pqueue pqueue.c)

# create executable
add_executable(test_pqueue test_pqueue.c)

# link the library with test executable
target_link_libraries(test_pqueue pqueue)