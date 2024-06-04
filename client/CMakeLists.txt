cmake_minimum_required(VERSION 3.20.0)
project(ChatClient VERSION 1.0.0)

add_executable(${PROJECT_NAME} client.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC chat-client)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)