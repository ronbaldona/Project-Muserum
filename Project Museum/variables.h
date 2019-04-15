#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Model.h"

typedef glm::mat3 mat3;
typedef glm::mat4 mat4;
typedef glm::vec3 vec3;
typedef glm::vec4 vec4;

#ifdef MAINPROGRAM 
#define EXTERN 
#else 
#define EXTERN extern 
#endif

EXTERN Shader* testShader;
// Camera setttings
EXTERN mat4 projMat;
EXTERN mat4 viewMat;

#ifdef MAINPROGRAM
GLFWwindow* window = nullptr;
unsigned int width = 800;
unsigned int height = 600;
float fovY = 90.0f;
vec3 camPos(0.0f, 0.0f, 5.0f);
vec3 camLookAt(0.0f, 0.0f, 0.0f);
vec3 camUp(0.0f, 1.0f, 0.0f);
#else
EXTERN GLFWwindow* window;
EXTERN unsigned int width, height;
EXTERN float fovY;
EXTERN vec3 camPos;
EXTERN vec3 camLookAt;
EXTERN vec3 camUp;
#endif
