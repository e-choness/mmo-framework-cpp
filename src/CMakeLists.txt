set(SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
set(INCLUDE_DIR "${SOURCE_DIR}/include")

file(GLOBS HEADER_LIST ${INCLUDE_DIR}/*.h ${INCLUDE_DIR}/*.hpp)
file(GLOBS SOURCE_LIST ${SOURCE_DIR}/*.c ${SOURCE_DIR}/*.cpp)

add_library(source_lib ${SOURCE_LIST} ${HEADER_LIST})

target_include_directories(source_lib PUBLIC ${INCLUDE_DIR})