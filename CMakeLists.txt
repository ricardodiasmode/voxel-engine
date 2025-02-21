cmake_minimum_required(VERSION 3.19)
project(voxelengine)
set(CMAKE_CXX_STANDARD 23)

add_subdirectory(include/glfw)

set(GLM_DIR "${CMAKE_SOURCE_DIR}/thirdparty/glm")

set(FREETYPE_DIR "${CMAKE_SOURCE_DIR}/thirdparty/freetype-2.13.3")
add_subdirectory(${FREETYPE_DIR} freetype_build)

# Create the executable, making sure to compile glad.c
file(GLOB_RECURSE PROJECT_SOURCES 
    "src/*.cpp" 
    "src/*.c" 
    "src/utils/*.cpp" 
)
add_executable(voxelengine ${PROJECT_SOURCES})

set(SHADER_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/opengl/shaders)

# Define the destination directory (where the executable runs)
set(SHADER_DEST_DIR ${CMAKE_BINARY_DIR}/shaders)

# Ensure the shaders are copied to the build directory
file(COPY ${SHADER_SOURCE_DIR} DESTINATION ${CMAKE_BINARY_DIR})

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/resources/fonts/arial)

# Copy the font file to the build directory
file(COPY ${CMAKE_SOURCE_DIR}/resources/fonts/arial/ARIAL.ttf
     DESTINATION ${CMAKE_BINARY_DIR}/resources/fonts/arial)

# Include your project�s headers (glad.h will be found inside include/)
target_include_directories(voxelengine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")
target_include_directories(voxelengine PRIVATE ${GLM_DIR})

# Link GLFW to the executable
target_link_libraries(voxelengine PRIVATE glfw)
target_link_libraries(voxelengine PRIVATE freetype)
