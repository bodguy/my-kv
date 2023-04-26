cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
project(my-kv)

file(GLOB_RECURSE MY_KV_SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${MY_KV_SOURCES})