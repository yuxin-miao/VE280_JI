cmake_minimum_required(VERSION 3.15)
project(Demo_Course)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -pedantic")

add_executable(Demo_Course main.cpp)
add_executable(Try try.cpp)