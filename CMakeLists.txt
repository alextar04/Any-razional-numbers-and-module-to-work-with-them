cmake_minimum_required(VERSION 3.10)
project(RazionalSlau C)

set(CMAKE_C_STANDARD 99)

add_executable(RazionalSlau input.c input.h OperationsModule.c OperationsModule.h GaussSlau.c GaussSlau.h RUN.c)