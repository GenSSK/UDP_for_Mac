cmake_minimum_required(VERSION 3.10)
project(UDP_for_Mac)

set(CMAKE_CXX_STANDARD 14)

find_package(Threads REQUIRED)

add_executable(UDP_for_Mac main.cpp client_thread.h)

target_link_libraries(UDP_for_Mac Threads::Threads)