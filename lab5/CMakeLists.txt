cmake_minimum_required(VERSION 3.27)
project(lab5 C)

set(CMAKE_C_STANDARD 11)

add_executable(lab5 sigusr1.c
        catcher.c
        sender.c
        sender.c)
