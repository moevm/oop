# Only for testing purposes!

cmake_minimum_required(VERSION 3.15.3)
project(logic)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/cmakebuild)

file(GLOB_RECURSE sources src/native/*)
list(REMOVE_ITEM sources ${CMAKE_CURRENT_SOURCE_DIR}/src/native/index.cpp)

add_executable(logic ${sources})

set_target_properties(
    logic
    PROPERTIES
        OUTPUT_NAME "logic"
        SUFFIX ".exe"
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)
