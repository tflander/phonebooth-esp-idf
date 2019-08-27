FILE(GLOB SUT_SRC ../main/*.c)
FILE(GLOB TEST_SRC *.c)
FILE(GLOB MOCK_SRC ${MOCK_DIR}/*.c)

include_directories(SYSTEM ${MOCK_DIR})
include_directories(SYSTEM ${UNITY_DIR})
add_executable(${PROJECT_TEST} ${TEST_SRC} ${SUT_SRC} ${MOCK_SRC})
target_link_libraries(${PROJECT_TEST} ${LIB_UNITY})
