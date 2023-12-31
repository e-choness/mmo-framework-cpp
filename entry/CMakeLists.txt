cmake_minimum_required(VERSION 3.20.0)
project(mmo-entry VERSION 1.0.0)

add_executable(mmo entry.cpp)
target_link_libraries(mmo PRIVATE source_lib boost_system)