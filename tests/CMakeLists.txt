# Add GoogleTest
find_package(GTest CONFIG REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(nntp-test
        testClient.cpp
        test_connection.cpp
        testRope.cpp
)

#target_link_libraries(nntp-test PUBLIC nntp GTest::gmock_main)
target_compile_features(nntp-test PUBLIC cxx_std_20)