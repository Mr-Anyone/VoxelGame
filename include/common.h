#ifndef COMMON_H
#define COMMON_H

#include <GLFW/glfw3.h>
#include <glad/glad.h>

// the following are a list of common functions
GLFWwindow* opengl_init();
void clearBuffer();

// Regarding Mouse and Input (Callbacks)
void processInput(GLFWwindow* window);
void mouseCallback();

// Vertices for a cube 
#endif 