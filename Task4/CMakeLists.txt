cmake_minimum_required(VERSION 3.5)
project(Task4)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O0")

set(SOURCE_FILES
        program.cpp
        RandomChar.cpp
        RandomChar.h
        TestObject.cpp
        TestObject.h)

add_executable(Task4 ${SOURCE_FILES})