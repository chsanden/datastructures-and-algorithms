cmake_minimum_required(VERSION 4.0)
project(SimpleSearch)

set(CMAKE_CXX_STANDARD 20)

add_executable(SimpleSearch main.cpp
        EBankAccountType.h
        TBankAccount.cpp
        TBankAccount.h
        TLinkedList.h
        SearchSummary.h
        FCompareAccount.h
)
