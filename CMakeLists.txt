cmake_minimum_required(VERSION 3.5)

SET(TDD FALSE CACHE BOOL "Enable local TDD development cycle")
if( NOT TDD )
    include($ENV{IDF_PATH}/tools/cmake/project.cmake)
endif()

project(phonebooth-esp-idf)

IF( TDD )
  SET(MOCK_DIR ${PROJECT_SOURCE_DIR}/mock)

  SET(PROJECT_TEST ${PROJECT_NAME}-test)
  SET(LIB_UNITY unity)

  add_subdirectory(test)
  add_subdirectory(unity)
  add_dependencies(${PROJECT_TEST} ${LIB_UNITY})
ENDIF()