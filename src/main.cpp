#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream> 

#include "shader.h"
#include "camera.h"
#include "common.h"

extern constexpr int width_g {800};
extern constexpr int height_g {600};

int main() 
{
    GLFWwindow* window {opengl_init()};
    
    while(!glfwWindowShouldClose(window))
    {
        processInput(window);
        clearBuffer();

        glfwPollEvents();    
        glfwSwapBuffers(window);
    }
    return 0;
}