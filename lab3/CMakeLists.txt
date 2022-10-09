cmake_minimum_required(VERSION 2.8.11)
project(lab3cmake)
set(SOURCE main.c my_lib.c)
add_executable(MyProject ${SOURCE})
add_library(Project SHARED main.c)

