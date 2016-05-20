cmake_minimum_required(VERSION 3.5)
project(Task6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -Wall")

set(SOURCE_FILES
    node.cpp
    node.hpp
    operators.cpp
    operators.hpp
    valuenode.cpp
    valuenode.hpp
    program.cpp)

add_executable(Task6 ${SOURCE_FILES})
