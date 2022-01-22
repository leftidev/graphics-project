cmake_minimum_required(VERSION 3.10)

# Set the project name
project(Graphics)

set(CMAKE_CXX_STANDARD 11)  # for c++11

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

set(SOURCE_FILES main.cpp)
add_executable(Graphics ${SOURCE_FILES})

# Add warnings
target_compile_options(Graphics PRIVATE -Wall -Wextra -Wpedantic -Werror)