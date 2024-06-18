cmake_minimum_required(VERSION 3.20.0)
project(ChatAppLib VERSION 1.0.0)

# Set include and source paths for server
set(CHAT_SERVER_LIB chat-server)
set(CHAT_SERVER_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/server)
set(CHAT_SERVER_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/server)

# Set include and source paths for client
set(CHAT_CLIENT_LIB chat-client)
set(CHAT_CLIENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/client)
set(CHAT_CLIENT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/client)

# Asio definitions
set(ASIO_DEFINITION_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/extern)

# Global common headers
set(COMMON_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/common)

# Network definitions
set(NETWORK_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/network)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.84.0 REQUIRED CONFIG)

# Library
add_library(${CHAT_SERVER_LIB}
        ${CHAT_SERVER_SOURCE_DIR}/custom_server.cpp)

add_library(${CHAT_CLIENT_LIB}
        ${CHAT_CLIENT_SOURCE_DIR}/custom_client.cpp)

# Add headers
target_include_directories(${CHAT_SERVER_LIB} PUBLIC
        ${COMMON_INCLUDE_DIR}
        ${NETWORK_INCLUDE_DIR}
        ${ASIO_DEFINITION_INCLUDE_DIR}
        ${CHAT_SERVER_INCLUDE_DIR}
        ${Boost_INCLUDE_DIRS})

target_include_directories(${CHAT_CLIENT_LIB} PUBLIC
        ${COMMON_INCLUDE_DIR}
        ${NETWORK_INCLUDE_DIR}
        ${ASIO_DEFINITION_INCLUDE_DIR}
        ${CHAT_CLIENT_INCLUDE_DIR}
        ${Boost_INCLUDE_DIRS})

target_link_directories(${CHAT_SERVER_LIB}
        PUBLIC
        boost::boost)

target_link_directories(${CHAT_CLIENT_LIB}
        PUBLIC
        boost::boost)


# Set preprocessor definition to specified version.
target_compile_features(${CHAT_SERVER_LIB} PRIVATE cxx_std_20)
target_compile_features(${CHAT_CLIENT_LIB} PRIVATE cxx_std_20)

target_compile_definitions(${CHAT_SERVER_LIB} PUBLIC CHAT_SERVER_VERSION="1.0")
target_compile_definitions(${CHAT_CLIENT_LIB} PUBLIC CHAT_CLIENT_VERSION="1.0")