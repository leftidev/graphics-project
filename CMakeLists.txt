cmake_minimum_required(VERSION 3.10)

# Set the project name
project(Graphics VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)  # for c++11
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(WIN32)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/windows-bin)
elseif(UNIX AND NOT APPLE)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/linux-bin)
endif(WIN32)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

set(SOURCE_FILES main.cpp glad.c)

add_executable(Graphics ${SOURCE_FILES})

if(WIN32)
    target_link_libraries(Graphics PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/libglfw3dll.a)
    target_include_directories(Graphics PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
elseif(UNIX AND NOT APPLE)
    find_package(glfw3 REQUIRED)
    find_package(OpenGL REQUIRED)
    set(OpenGL_GL_PREFERENCE(GLVND))
    target_link_libraries(Graphics OpenGL ${GLFW3_LIBRARY})
    target_include_directories(Graphics PRIVATE ${GLFW3_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include)
    target_compile_options(Graphics PRIVATE -lglfw -lOpenGL -Wall -Wextra -Werror)
    set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")
endif(WIN32)
