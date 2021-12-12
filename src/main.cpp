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

extern constexpr int width_g {800};
extern constexpr int height_g {600};
glm::mat4 projection_g {glm::perspective(glm::radians(45.0f), static_cast<float> (width_g) / height_g, 0.1f, 1000.0f)};
Camera camera_g {glm::vec3(0.0f, 0.0f, -2.0f), glm::vec3(0.0f, 0.0f, 1.0), glm::vec3(0.0f, 1.0f, 0.0f)};

static void loadTexture()
{
    unsigned int m_texture;
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture); 

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char *data = stbi_load("./../res/texture/brickwall.jpeg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

int main() 
{
    GLFWwindow* window {opengl_init()};
    Shader shader {"./../res/shader/vertexShader.glsl", "./../res/shader/fragmentShader.glsl"};
    
    // ChunkManager manager;
    // manager.setRenderDistance(2);
    loadTexture();
    Chunk chunk; 
    makeTestChunk(chunk, 0, 0 );

    while(!glfwWindowShouldClose(window))
    {
        processInput(window);
        clearBuffer();

        // drawing the first triangle
        // manager.render(shader, camera_g.getPosition());
        chunk.render(shader); 

        glfwPollEvents();    
        glfwSwapBuffers(window);
    }
    return 0;
}