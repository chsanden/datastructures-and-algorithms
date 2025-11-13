cmake_minimum_required(VERSION 4.0)
project(TheAlgorithmicOrganizer)

set(CMAKE_CXX_STANDARD 20)

add_executable(TheAlgorithmicOrganizer main.cpp
        main.h
        BankAccount.h
        BankAccount.cpp
        BankAccountList.cpp
        BankAccountList.h
        FileReaderUtils.cpp
        FileReaderUtils.h
        ReadNames.cpp
        SharedLib.h
        Utils.cpp
        Sort.cpp
        Sort.h
)
