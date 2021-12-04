#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream> 

#include "shader.h"
#include "camera.h"
#include "common.h"
#include "chunk.h"

extern constexpr int width_g {800};
extern constexpr int height_g {600};

int main() 
{
    GLFWwindow* window {opengl_init()};
    Shader shader {"./../res/shader/vertexShader.glsl", "./../res/shader/fragmentShader.glsl"};
    
    float vertices[] = 
    {
        -0.5f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
    };
    
    unsigned int VAO, VBO; 
    glGenVertexArrays(1, &VAO); 
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO); 
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*) 0); 
    glEnableVertexAttribArray(0); 

    while(!glfwWindowShouldClose(window))
    {
        processInput(window);
        clearBuffer();

        // drawing the first triangle
        shader.use(); 
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3); 

        glfwPollEvents();    
        glfwSwapBuffers(window);
    }
    return 0;
}