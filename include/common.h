#ifndef COMMON_H
#define COMMON_H

#include <GLFW/glfw3.h>
#include <glad/glad.h>

// the following are a list of common functions
GLFWwindow* opengl_init();
void clearBuffer();
void processInput(GLFWwindow* window);

#endif 