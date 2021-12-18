#ifndef COMMON_H
#define COMMON_H

#include <GLFW/glfw3.h>
#include <glad/glad.h>

// A list  of constants
constexpr int width_g {1920};
constexpr int height_g {1080};

// the following are a list of common functions
GLFWwindow* opengl_init();
void clearBuffer();

// Regarding Mouse and Input (Callbacks)
void processInput(GLFWwindow* window);
void mouseCallback(GLFWwindow* window, double xPos, double yPos);

#endif 