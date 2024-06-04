cmake_minimum_required(VERSION 3.20.0)
project(ChatServer VERSION 1.0.0)

add_executable(${PROJECT_NAME} server.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC chat-server)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)