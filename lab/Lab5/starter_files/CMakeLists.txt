cmake_minimum_required(VERSION 3.15)
project(starter_files)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -pedantic")

add_executable(starter_files ex3.cpp factoredForm.cpp)