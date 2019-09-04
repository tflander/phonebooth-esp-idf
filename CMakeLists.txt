# This file is long and looks intimidating.  After you
# read the comments, strip all of them out and you will
# see that the file isn't quite so large or scary.
#######################################################

cmake_minimum_required(VERSION 3.5)

# Set the project name
project(phonebooth-esp-idf)

# If we call cmake with -DTDD=true we enable the TDD features
# of this build.
SET(TDD FALSE CACHE BOOL "Enable local TDD development cycle")

# If the TDD flag was not set we should use the esp32 native toolchain
if( NOT TDD )
    # This includes the esp32 toolchain's native CMake file
    # Only necessary for building and flashing to the esp32 device
    include($ENV{IDF_PATH}/tools/cmake/project.cmake)
endif()

IF( TDD )
    # This includes the build steps necessary for test driving our code
    include(tdd.cmake)
ENDIF()