# create library for selection_sort 
add_library(selection_sort selection_sort.c)

# create executable
add_executable(test_selection_sort test_selection_sort.c)

# link the library with test executable
target_link_libraries(test_selection_sort selection_sort)