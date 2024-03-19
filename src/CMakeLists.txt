cmake_minimum_required(VERSION 3.20.0)
project(HelloLibrary VERSION 1.0.0)

# Set include and source paths
set(HELLO_LIB say-hello)
set(HELLO_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(HELLO_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)


set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.84.0 REQUIRED CONFIG)



# Library
add_library(${HELLO_LIB}
        ${HELLO_SOURCE_DIR}/hello.cpp)

# Add headers
target_include_directories(${HELLO_LIB} PUBLIC
        ${HELLO_INCLUDE_DIR}
        ${Boost_INCLUDE_DIRS})

target_link_directories(${HELLO_LIB}
        PUBLIC
        boost::boost)


# Set preprocessor definition to specified version.
target_compile_features(${HELLO_LIB} PRIVATE cxx_std_20)
target_compile_definitions(${HELLO_LIB} PUBLIC SAY_HELLO_VERSION="1.1")