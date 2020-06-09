cmake_minimum_required(VERSION 3.15)
project(p2_starters)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -pedantic")

add_executable(p2_starters p2.cpp simulation.cpp)