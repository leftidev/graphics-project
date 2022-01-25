add_library(project_folder INTERFACE)
target_include_directories(project_folder INTERFACE 
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)

# Add glad
add_library(glad glad.c)
target_link_libraries(glad PRIVATE project_folder)


# Main executable
add_executable(App App/main.cpp)
if(WIN32)
    target_link_libraries(App
        PRIVATE
            project_folder
            project_options
            ${PROJECT_SOURCE_DIR}/include/libglfw3dll.a
            glad
            window
    )
elseif(UNIX AND NOT APPLE)
    # Find packages
    find_package(glfw3 REQUIRED)
    find_package(OpenGL REQUIRED)

    target_link_libraries(App
    PRIVATE
        project_folder
        project_options
        OpenGL
        ${GLFW3_LIBRARY}
        glad
        window
    )
    target_compile_options(App PRIVATE -lglfw -lOpenGL -Wall -Wextra -Werror)
    set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")
endif(WIN32)


add_subdirectory(Renderer)