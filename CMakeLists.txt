cmake_minimum_required(VERSION 3.20)

# set the project name
project(DSA)

# specify the c standard
set(CMAKE_C_STANDARD 11)

# add the algorithm
add_subdirectory(algo)

# add the data structures
add_subdirectory(ds)

