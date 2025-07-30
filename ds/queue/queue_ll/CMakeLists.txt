# create library for linked list queue
add_library(queue_ll queue_ll.c)

# create executable
add_executable(test_queue_ll test_queue_ll.c)

# link the library with test executable
target_link_libraries(test_queue_ll queue_ll)