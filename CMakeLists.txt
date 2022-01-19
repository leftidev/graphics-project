cmake_minimum_required(VERSION 3.10)

# Set the project name
project(Graphics)

# Add the executable
add_executable(Graphics main.cpp)

# Add warnings
target_compile_options(Graphics PRIVATE -Wall -Wextra -Wpedantic -Werror)