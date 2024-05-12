cmake_minimum_required(VERSION 3.27)
project(APT_Vending_Machine)

set(CMAKE_CXX_STANDARD 14)

include_directories(code)

add_executable(APT_Vending_Machine
        code/Coin.cpp
        code/Coin.h
        code/ftt.cpp
        code/LinkedList.cpp
        code/LinkedList.h
        code/Node.cpp
        code/Node.h)
