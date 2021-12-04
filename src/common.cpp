#include <iostream> 
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "common.h"

extern int width_g;
extern int height_g;

GLFWwindow* opengl_init()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
    std::cout << "Creating Window with Length: " << width_g << " Height: " << height_g << std::endl;
    GLFWwindow* window = glfwCreateWindow(width_g, height_g, "VoxelGame", NULL, NULL);
    
    if(window == nullptr)
    {
        std::cout << "Cannot Create Window" << std::endl; 
    }
    
    glfwMakeContextCurrent(window);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }    
    
    glViewport(0, 0, width_g, height_g);
    return window;
}

void clearBuffer()
{
    // Clear Color Buffer
    glClearColor(0.3f, 0.2f, 0.2f, 1.0f); 
    glClear(GL_COLOR_BUFFER_BIT);
}

void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
}

void mouseCallback(int x, int y)
{

}