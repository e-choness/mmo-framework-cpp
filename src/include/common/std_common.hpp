#pragma once
#include <memory>
#include <thread>
#include <mutex>
#include <deque>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <cstdint>

#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif

typedef std::chrono::system_clock::time_point TimePoint;

inline auto getNow(){
    return std::chrono::system_clock::now();
}