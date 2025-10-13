cmake_minimum_required(VERSION 4.0)
project(assignment1)

set(CMAKE_CXX_STANDARD 20)

add_executable(assignment1 main.cpp
        TMovie.h
        TMovie.cpp
        TMovieList.cpp
        TMovieList.h
        TMovieNode.cpp
        TMovieNode.h)
