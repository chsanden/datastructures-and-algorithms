cmake_minimum_required(VERSION 3.31)
project(IKT203)

set(CMAKE_CXX_STANDARD 20)

add_executable(IKT203 main.cpp
        TMovie.cpp
        TMovie.h
        TMovieNode.cpp
        TMovieNode.h
        TMovieList.cpp
        TMovieList.h)
