cmake_minimum_required(VERSION 3.5)
project(Task7)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall")

set(SOURCE_FILES
    myvector.h
    main.cpp)

add_executable(Task7 ${SOURCE_FILES})
