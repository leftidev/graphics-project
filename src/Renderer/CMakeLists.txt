# Create renderer_folder target
add_library(renderer_folder INTERFACE)
target_include_directories(renderer_folder INTERFACE .)
target_include_directories(renderer_folder INTERFACE ${PROJECT_SOURCE_DIR}/include)

add_library(window Window.cpp Shader.cpp Cube.cpp)

target_link_libraries(window
    PUBLIC
        project_options
        renderer_folder
        ${PROJECT_SOURCE_DIR}/include/libglfw3dll.a
)
