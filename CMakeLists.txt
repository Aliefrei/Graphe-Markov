cmake_minimum_required(VERSION 3.30)
project(test)

set(CMAKE_CXX_STANDARD 20)

add_executable(main
        main.c
        part1.c
        part1.h
        part2.c
        part2.h
        hasse.c
        hasse.h
)
