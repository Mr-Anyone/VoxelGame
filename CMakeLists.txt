cmake_minimum_required(VERSION 3.0.0)
project(VoxelGame)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(3rd-party)

add_executable(VoxelGame 
    src/main.cpp 
    src/common.cpp
    src/chunk.cpp
    src/chunkManager.cpp
    src/terrain.cpp
)
    
target_link_libraries(VoxelGame glfw noise-static glm::glm glad libnoiseutil-static)
set(THIRD_PARTY_INCLUDE ${PROJECT_SOURCE_DIR}/3rd-party/glad/include ${PROJECT_SOURCE_DIR}/3rd-party/libnoise/src ${PROJECT_SOURCE_DIR}/3rd-party/stbi_image ${PROJECT_SOURCE_DIR}/3rd-party/noiseutil ${PROJECT_SOURCE_DIR}/3rd-party)
target_include_directories(VoxelGame PRIVATE  ${THIRD_PARTY_INCLUDE} ${PROJECT_SOURCE_DIR}/include)