cmake_minimum_required(VERSION 3.18.1)

project(ForThreadsTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ForThreadsTest main.cpp for_threads.h)
