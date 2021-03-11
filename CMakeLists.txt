cmake_minimum_required(VERSION 3.17)
project(chess2 C)

set(CMAKE_C_STANDARD 11)

include_directories(src)

add_executable(chess2
        src/board.c
        src/board.h
        src/filem.c
        src/filem.h
        src/main.c)
