cmake_minimum_required(VERSION 3.19)
project(voxelengine)
set(CMAKE_CXX_STANDARD 23)

# Add GLFW as a subdirectory (assuming you placed it in include/glfw)
add_subdirectory(include/glfw)

# Create the executable, making sure to compile glad.c
add_executable(voxelengine src/main.cpp src/opengl/glad/glad.c)

file(COPY ${CMAKE_SOURCE_DIR}/src/opengl/shaders DESTINATION ${CMAKE_BINARY_DIR})

# Include your project’s headers (glad.h will be found inside include/)
target_include_directories(voxelengine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")

# Link GLFW to the executable
target_link_libraries(voxelengine PRIVATE glfw)
