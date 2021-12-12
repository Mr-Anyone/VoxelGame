#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream> 
#include <glm/glm.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stbi_image.h>

#include "shader.h"
#include "camera.h"
#include "common.h"
#include "chunk.h"
#include "chunkManager.h"
#include "terrain.h"
#define RENDER_TEST_CHUNK 

extern constexpr int width_g {800};
extern constexpr int height_g {600};
glm::mat4 projection_g {glm::perspective(glm::radians(45.0f), static_cast<float> (width_g) / height_g, 0.1f, 1000.0f)};
Camera camera_g {glm::vec3(0.0f, 0.0f, -2.0f), glm::vec3(0.0f, 0.0f, 1.0), glm::vec3(0.0f, 1.0f, 0.0f)};

int main() 
{
    GLFWwindow* window {opengl_init()};
    Shader shader {"./../res/shader/vertexShader.glsl", "./../res/shader/fragmentShader.glsl"};
    
#ifdef RENDER_TEST_CHUNK
    Chunk chunk; 
    makeTestChunk(chunk, 0, 0);
#else
    ChunkManager manager;
    manager.setRenderDistance(3);
#endif

    while(!glfwWindowShouldClose(window))
    {
        processInput(window);
        clearBuffer();

        // drawing the first triangle
#ifdef RENDER_TEST_CHUNK
        chunk.render(shader);
#else 
        manager.render(shader, camera_g.getPosition());
#endif
    
        glfwPollEvents();    
        glfwSwapBuffers(window);
    }
    return 0;
}