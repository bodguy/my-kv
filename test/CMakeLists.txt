enable_testing()

find_package(GTest CONFIG REQUIRED)

set(TEST_TARGET_NAME "${PROJECT_NAME}_test")
set(TEST_DIR "${CMAKE_SOURCE_DIR}/test/src")

# test
file(GLOB_RECURSE TEST_SOURCE_FILES
        "${TEST_DIR}/*.h"
        "${TEST_DIR}/*.hpp"
        "${TEST_DIR}/*.cpp"
        )
add_executable("${TEST_TARGET_NAME}" ${TEST_SOURCE_FILES})
target_include_directories("${TEST_TARGET_NAME}" PRIVATE ${SERVER_SOURCE_DIR})
target_link_libraries("${TEST_TARGET_NAME}" PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
add_test(AllTestsInMain ${TEST_TARGET_NAME})

include(GoogleTest)
gtest_discover_tests(${TEST_TARGET_NAME})