cmake_minimum_required(VERSION 3.20.0)
project(MMO
        VERSION 1.0
        DESCRIPTION "MMO Framework"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(entry)
add_subdirectory(src)
add_subdirectory(extern)
add_subdirectory(tests)
