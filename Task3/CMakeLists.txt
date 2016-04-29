cmake_minimum_required(VERSION 3.5)
project(Task3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        dynamicobjectlist.cpp
        dynamicobjectlist.hpp
        object.cpp
        object.h
        program.cpp)

add_executable(Task3 ${SOURCE_FILES})