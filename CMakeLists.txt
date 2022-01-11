cmake_minimum_required(VERSION 3.22)
project(conn4)

set(CMAKE_CXX_STANDARD 20)

add_executable(conn4 main.cpp lib/src/board.cpp)

include_directories(lib/include)
