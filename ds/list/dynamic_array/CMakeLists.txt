# create library for dynamic array
add_library(darray darray.c)

# create executable
add_executable(test_darray test_darray.c)

# link the library with test executable
target_link_libraries(test_darray darray)