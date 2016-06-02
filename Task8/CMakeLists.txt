cmake_minimum_required(VERSION 3.5)
project(Task8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall")

set(SOURCE_FILES
    program.cpp
    unittests.hpp
    target.hpp)

add_executable(Task8 ${SOURCE_FILES})
