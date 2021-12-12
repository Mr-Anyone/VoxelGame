cmake_minimum_required(VERSION 3.0.0)
project(VoxelGame)

set(CMAKE_CXX_STANDARD 17)

find_package(glfw3 3.3 REQUIRED)

add_executable(VoxelGame 
    src/main.cpp 
    src/common.cpp
    src/chunk.cpp
    src/chunkManager.cpp
    src/terrain.cpp
    3rd-party/glad.c
    3rd-party/noiseutils.cpp
)
    
target_link_libraries(VoxelGame glfw /usr/local/lib/libnoise.a)
target_include_directories(VoxelGame PRIVATE ${PROJECT_SOURCE_DIR}/3rd-party ${PROJECT_SOURCE_DIR}/include)