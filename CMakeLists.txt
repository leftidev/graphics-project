cmake_minimum_required(VERSION 3.16)

# Set the project name
project(Graphics VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)  # for c++11
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(WIN32)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/windows-bin)
elseif(UNIX AND NOT APPLE)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/linux-bin)
endif(WIN32)

# Add cmake modules
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

# Create interface
add_library(project_options INTERFACE)

# Add source folder
add_subdirectory(src)

# Enable testing and define tests
message("BUILDING TESTS..")
enable_testing()
#add_subdirectory(UnitTests)