# specify the source files
set(SOURCES
    selection_sort.c
    bubble_sort.c
    insertion_sort.c
)

# specify the test files directory
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)

# add the test files
file(GLOB TEST_FILES ${TEST_DIR}/*.c)

# create a list to hold the executable
foreach(TEST_SOURCE ${TEST_FILES})
    # get the file name with out extension
    get_filename_component(EXECUTABLE_NAME ${TEST_SOURCE} NAME_WE)

    # generate executable for each test source files
    add_executable(${EXECUTABLE_NAME} ${TEST_SOURCE} ${SOURCES})
endforeach()


# finally specify the header file
include_directories(${CMAKE_CURRENT_SOURCE_DIR})