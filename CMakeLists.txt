cmake_minimum_required(VERSION 3.20)
project(Assighment_1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Assighment_1
        base.h
        FCFS.cpp
        main.cpp
        SCAN.cpp
        SSTF.cpp)
