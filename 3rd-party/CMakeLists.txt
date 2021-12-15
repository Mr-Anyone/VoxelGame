set(THIRD_PARTY_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/3rd-party/glad/include)

add_library(glad STATIC glad/src/glad.c)
target_include_directories(glad PRIVATE ${THIRD_PARTY_INCLUDE_DIR})

# Other Libraries
add_subdirectory(glm)
add_subdirectory(glfw)
add_subdirectory(libnoise)
