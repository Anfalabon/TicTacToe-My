

cmake_minimum_required(VERSION 3.10)

project(TicTacToe)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
    #../some_definition.h
    #../player.h
    #../gui.h
    #../match.h
    #../player.cpp
    #../match.cpp
    #../run_functions.cpp
    ../main.cpp
)


add_executable(game ${SOURCE_FILES})

target_include_directories(game PRIVATE include)

set(CMAKE_CXX_COMPILER "clang++")


































