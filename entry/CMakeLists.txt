cmake_minimum_required(VERSION 3.20.0)
project(HelloEntry VERSION 1.0.0)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC say-hello)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

#include(${SCRIPTS_DIR}/PrintVariables.cmake)
#print_variables()