cmake_minimum_required(VERSION 3.20)

# set the project name
project(DataStructure)

# specify the c standard
set(CMAKE_C_STANDARD 11)

# add the linked_list sub-directory
add_subdirectory(linked_list)

# add the doublee_linked_list sub-directory
add_subdirectory(double_linked_list)

# add the circular_linked_list sub-directory
add_subdirectory(circular_linked_list)

# add the header_linked_list sub-directory
add_subdirectory(header_linked_list)

# add the array stack sub-directory
add_subdirectory(stack_arr)

# add the linked list stack sub-directory
add_subdirectory(stack_ll)