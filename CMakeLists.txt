cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
project(my-kv)

find_package(spdlog CONFIG REQUIRED)
find_package(Threads REQUIRED)

set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
set(SERVER_SOURCE_DIR "${SOURCE_DIR}/server")
set(CLIENT_SOURCE_DIR "${SOURCE_DIR}/client")

set(SERVER_TARGET_NAME "${PROJECT_NAME}_server")
set(CLIENT_TARGET_NAME "${PROJECT_NAME}_client")

# server
file(GLOB_RECURSE SERVER_SOURCE_FILES
        "${SERVER_SOURCE_DIR}/*.h"
        "${SERVER_SOURCE_DIR}/*.hpp"
        "${SERVER_SOURCE_DIR}/*.cpp"
        )
add_executable(${SERVER_TARGET_NAME} ${SERVER_SOURCE_FILES})
target_include_directories(${SERVER_TARGET_NAME} PRIVATE ${SERVER_SOURCE_DIR})
target_link_libraries(${SERVER_TARGET_NAME} PRIVATE spdlog::spdlog)

# client
file(GLOB_RECURSE CLIENT_SOURCE_FILES
        "${CLIENT_SOURCE_DIR}/*.h"
        "${CLIENT_SOURCE_DIR}/*.hpp"
        "${CLIENT_SOURCE_DIR}/*.cpp"
        )
add_executable(${CLIENT_TARGET_NAME} ${CLIENT_SOURCE_FILES})
target_include_directories(${CLIENT_TARGET_NAME} PRIVATE ${CLIENT_SOURCE_DIR})
target_link_libraries(${CLIENT_TARGET_NAME} PRIVATE spdlog::spdlog)

add_subdirectory(test)