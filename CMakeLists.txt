cmake_minimum_required(VERSION 3.13)
project(ft_ls2 C)

set(CMAKE_C_STANDARD 11)

include_directories(includes)

add_executable(ft_ls2
        includes/lsft.h
        src/sort_classic.c
        main.c)
