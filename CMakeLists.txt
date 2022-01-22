cmake_minimum_required(VERSION 3.10)


# Sample toolchain file for building for Windows from an Ubuntu Linux system.
#
# Typical usage:
#    *) install cross compiler: `sudo apt-get install mingw-w64`
#    *) mkdir buildMingw64 && cd buildMingw64
#    *) cmake -DCMAKE_TOOLCHAIN_FILE=~/Toolchain-Ubuntu-mingw64.cmake ..
#


set(CMAKE_SYSTEM_NAME Windows)
set(TOOLCHAIN_PREFIX x86_64-w64-mingw32)
set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}-gcc-posix)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}-g++-posix)



# modify default behavior of FIND_XXX() commands to
# search for headers/libs in the target environment and
# search for programs in the build host environment
#set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
#set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
#set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# Set the project name
project(Graphics VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)  # for c++11
set(CMAKE_CXX_STANDARD_REQUIRED True)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

set(SOURCE_FILES main.cpp glad.c)

add_executable(Graphics ${SOURCE_FILES})

#if(WIN32) 
    target_link_libraries(Graphics PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/libglfw3dll.a)
    target_include_directories(Graphics PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
#else()
    #find_package(glfw3 REQUIRED)
    #find_package(OpenGL REQUIRED)
    #set(OpenGL_GL_PREFERENCE(GLVND))
    #target_link_libraries(Graphics OpenGL ${GLFW3_LIBRARY})
    #target_include_directories(Graphics PRIVATE ${GLFW3_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include)
#endif()




# Compile options
#if(WIN32) 
    target_compile_options(Graphics PRIVATE -luser32 -lgdi32 -lopengl32 -libglfw3dll.a)
    #target_compile_options(Graphics.exe PRIVATE -libglfw3dll.a -Wall -Wextra -Werror -luser32 -lgdi32 -lopengl32)
#else()
#    target_compile_options(Graphics PRIVATE -ldl -lglfw -lOpenGL -Wall -Wextra -Werror)
#endif()

