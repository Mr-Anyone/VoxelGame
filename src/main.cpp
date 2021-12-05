#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream> 
#include <glm/glm.hpp>

#include "shader.h"
#include "camera.h"
#include "common.h"
#include "chunk.h"

extern constexpr int width_g {800};
extern constexpr int height_g {600};
glm::mat4 projection_g {glm::perspective(glm::radians(45.0f), static_cast<float> (width_g) / height_g, 0.1f, 1000.0f)};
Camera camera_g {glm::vec3(0.0f, 0.0f, -2.0f), glm::vec3(0.0f, 0.0f, 1.0), glm::vec3(0.0f, 1.0f, 0.0f)};

int main() 
{
    GLFWwindow* window {opengl_init()};
    Shader shader {"./../res/shader/vertexShader.glsl", "./../res/shader/fragmentShader.glsl"};
    
    // float vertices[] = {
    //     -1.0f, -1.0f, -1.0f,  
    //      1.0f, -1.0f, -1.0f,  
    //      1.0f,  1.0f, -1.0f,  
    //      1.0f,  1.0f, -1.0f,  
    //     -1.0f,  1.0f, -1.0f,  
    //     -1.0f, -1.0f, -1.0f,  

    //     -1.0f, -1.0f,  1.0f,  
    //      1.0f, -1.0f,  1.0f,  
    //      1.0f,  1.0f,  1.0f,  
    //      1.0f,  1.0f,  1.0f,  
    //     -1.0f,  1.0f,  1.0f,  
    //     -1.0f, -1.0f,  1.0f,  

    //     -1.0f,  1.0f,  1.0f,  
    //     -1.0f,  1.0f, -1.0f,  
    //     -1.0f, -1.0f, -1.0f,  
    //     -1.0f, -1.0f, -1.0f,  
    //     -1.0f, -1.0f,  1.0f,  
    //     -1.0f,  1.0f,  1.0f,  

    //      1.0f,  1.0f,  1.0f,  
    //      1.0f,  1.0f, -1.0f,  
    //      1.0f, -1.0f, -1.0f,  
    //      1.0f, -1.0f, -1.0f,  
    //      1.0f, -1.0f,  1.0f,  
    //      1.0f,  1.0f,  1.0f,  

    //     -1.0f, -1.0f, -1.0f,  
    //      1.0f, -1.0f, -1.0f,  
    //      1.0f, -1.0f,  1.0f,  
    //      1.0f, -1.0f,  1.0f,  
    //     -1.0f, -1.0f,  1.0f,  
    //     -1.0f, -1.0f, -1.0f,  

    //     -1.0f,  1.0f, -1.0f,  
    //      1.0f,  1.0f, -1.0f,  
    //      1.0f,  1.0f,  1.0f,  
    //      1.0f,  1.0f,  1.0f,  
    //     -1.0f,  1.0f,  1.0f,  
    //     -1.0f,  1.0f, -1.0f
    // };

    // unsigned int VAO, VBO; 
    // glGenVertexArrays(1, &VAO); 
    // glGenBuffers(1, &VBO);
    
    // glBindVertexArray(VAO); 
    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*) 0); 
    // glEnableVertexAttribArray(0); 

    Chunk chunk;
    makeTestChunk(chunk);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    while(!glfwWindowShouldClose(window))
    {
        processInput(window);
        clearBuffer();

        // drawing the first triangle
        shader.use(); 
        chunk.render(shader);
        // glBindVertexArray(VAO);
        // shader.setMat4("view", camera_g.getView());
        // shader.setMat4("model", glm::mat4 (1.0f));
        // shader.setMat4("projection", projection_g);
        // glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) /sizeof(float)); 

        glfwPollEvents();    
        glfwSwapBuffers(window);
    }
    return 0;
}