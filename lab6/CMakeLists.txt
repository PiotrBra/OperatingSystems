cmake_minimum_required(VERSION 3.27)
project(lab6 C)

set(CMAKE_C_STANDARD 11)

add_executable(lab6
        integrate.c
        reader.c
        calculator.c)
