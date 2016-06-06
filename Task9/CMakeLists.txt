cmake_minimum_required(VERSION 3.5)
project(Task9)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall")

set(SOURCE_FILES
    program.cpp
    policy.hpp
    consolepolicy.cpp
    consolepolicy.hpp
    filepolicy.cpp
    filepolicy.hpp
    logger.cpp
    logger.hpp)

add_executable(Task9 ${SOURCE_FILES})
