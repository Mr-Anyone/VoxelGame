#include <iostream> 
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "common.h"
#include "camera.h"
#include "stbi_image.h"

extern Camera camera_g;

void enableFaceCull(GLFWwindow* window)
{
    glEnable(GL_CULL_FACE); // Enable Face Culling
    glFrontFace(GL_CCW); // counter-clockwise
    glCullFace(GL_BACK); // does not render the back face
}

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
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
    glfwSetCursorPosCallback(window, mouseCallback);  
    
    stbi_set_flip_vertically_on_load(true);  
    
    // Enable Depth Buffer and face culling
    glEnable(GL_DEPTH_TEST);
//    enableFaceCull(window);
    return window;
}

void clearBuffer()
{
    // Clear Color Buffer
    glClearColor(0.3f, 0.2f, 0.2f, 1.0f); 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    constexpr float speed {1};
    
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera_g.moveFront(speed);
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera_g.moveFront(-speed);
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera_g.moveSide(-speed);
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera_g.moveSide(speed);

    static GLenum renderMode = GL_LINE; 
    if(glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)

    {
        glPolygonMode(GL_FRONT_AND_BACK, renderMode);
        switch(renderMode)
        {
            case GL_LINE: 
                renderMode = GL_FILL; 
                break; 
            case GL_FILL: 
                renderMode = GL_LINE;
                break;
        }
    }
}

void mouseCallback(GLFWwindow* window, double xPos, double yPos)
{
    static double previousX, previousY; 
    static bool first {true}; 
    if(first)
    {
        previousX = xPos; 
        previousY = yPos;
        
        first = false;
        return;
    }

    float sensitivity = 1;
    float xOffset =  xPos - previousX ;
    float yOffset =   previousY - yPos; 

    camera_g.rotate(xOffset, yOffset); 

    previousX = xPos; 
    previousY = yPos;
}