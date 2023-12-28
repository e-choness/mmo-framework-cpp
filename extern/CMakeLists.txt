add_library(asio
asio/asio/include/asio.hpp
asio/asio/src/asio.cpp)

target_include_directories(asio PUBLIC "${PROJECT_SOURCE_DIR}")