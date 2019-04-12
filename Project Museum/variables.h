#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#ifdef MAINPROGRAM 
#define EXTERN 
#else 
#define EXTERN extern 
#endif

EXTERN GLFWwindow* window = nullptr;

EXTERN unsigned int vertShader;
EXTERN unsigned int fragShader;

EXTERN int sizeX, sizeY;
