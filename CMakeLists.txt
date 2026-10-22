#Tell Cmake how to build the project

cmake_minimum_required(VERSION 3.20)

project(chess_console
    VERSION 0.1.0
    LANGUAGES CXX
)
include(CTest)
enable_testing()

add_executable(chess_console
    src/main.cpp
)
set_property(TARGET chess_console PROPERTY CXX_STANDARD 20)

target_include_directories(chess_console PRIVATE include)