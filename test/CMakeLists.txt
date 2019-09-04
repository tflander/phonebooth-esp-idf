# This file is long and looks intimidating.  After you
# read the comments, strip all of them out and you will
# see that the file isn't quite so large or scary.
#######################################################

# CMake file for the unit tests 

# FILE GLOBing: a unix concept where all files matching a wildcard
# pattern are collected as a group.

# A list of all of the files matching *.c in this directory
# will be assigned to the variable TEST_SRC
FILE(GLOB TEST_SRC *.c)

# A list of all of the files matching *.c in the MOCK_DIR directory
# will be assigned to the variable TEST_SRC (defined one level up)
FILE(GLOB MOCK_SRC ${MOCK_DIR}/*.c)

# A list of all src files in the System Under Test
FILE(GLOB SUT_SRC ../main/*.c)

# These make the mock directory and the unity directory 
# available as a source for header files, so if you have
# a file unity_fixture.h in the unity directory, you can 
# write  '#include <unity_fixture.h>' in a file and the
# compiler will know how to find it.
# This works the same for files under the mock directory.

include_directories(SYSTEM ${MOCK_DIR})
include_directories(SYSTEM ${UNITY_DIR})

# Tells cmake that we want to create an executable named 
# phonebooth-esp-idf-test (defined one level up).
add_executable(${PROJECT_TEST} ${TEST_SRC} ${SUT_SRC} ${MOCK_SRC})

# This says the that executable phonebooth-esp-idf-test will be
# linked with the unity library.
target_link_libraries(${PROJECT_TEST} ${LIB_UNITY})
