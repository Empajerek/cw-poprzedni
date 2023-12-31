cmake_minimum_required(VERSION 3.27)
project(cw_poprzedni)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(cw_poprzedni
        main.cpp
        prev.cpp
        prev.h)

add_executable(TEST
        prev.cpp
        prev.h)
