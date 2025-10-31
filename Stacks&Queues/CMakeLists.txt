cmake_minimum_required(VERSION 4.0)
project(Stacks_Queues)

set(CMAKE_CXX_STANDARD 20)

add_executable(Stacks_Queues main.cpp
        TStack.cpp
        TStack.h
        TQueue.cpp
        TQueue.h
        FUtils.h)
