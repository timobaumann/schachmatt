cmake_minimum_required(VERSION 3.27)
project(klosterhuber C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(klosterhuber
        main.c
        schach.c
        minimax.h)

add_executable(test
        tests.c schach.h schach.c list.h arraylist.c)