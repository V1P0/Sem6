cmake_minimum_required(VERSION 3.16)
project(lab3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_executable(radix radix.cpp src/fileread.cpp include/fileread.h include/graph_utill.h src/graph_utill.cc
        src/graph_utill.cc src/algorithms.cpp include/algorithms.h)

add_executable(dial dial.cpp src/fileread.cpp include/fileread.h include/graph_utill.h src/graph_utill.cc
        src/graph_utill.cc src/algorithms.cpp include/algorithms.h)

add_executable(binary_heap binary_heap.cpp src/fileread.cpp include/fileread.h include/graph_utill.h src/graph_utill.cc
        src/graph_utill.cc src/algorithms.cpp include/algorithms.h)
