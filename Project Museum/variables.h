#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

typedef glm::mat3 mat3;
typedef glm::mat4 mat4;
typedef glm::vec3 vec3;
typedef glm::vec4 vec4;

#ifdef MAINPROGRAM 
#define EXTERN 
#else 
#define EXTERN extern 
#endif

//EXTERN unsigned int vertShader, fragShader, shaderProgram;
EXTERN Shader* testShader;

#ifdef MAINPROGRAM
GLFWwindow* window = nullptr;
#else
EXTERN GLFWwindow* window;
#endif
