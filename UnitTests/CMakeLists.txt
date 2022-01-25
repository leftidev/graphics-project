include(CTest)

find_package(Boost REQUIRED COMPONENTS unit_test_framework)

add_executable(WindowTest WindowTest.cpp)
target_link_libraries(WindowTest
    PRIVATE
        project_folder
        project_options
        window
    )

