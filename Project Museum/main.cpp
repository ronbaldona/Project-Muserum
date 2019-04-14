#define MAINPROGRAM
#include "variables.h"

#include <iostream>
#include "TestTriangle.h"

inline void initializeGLFWSettings() {
	glfwInit();
	// We will be working with OpenGL 3.3 Core
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

inline bool initializeGLSettings() {
	// Load OpenGL function ptrs
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD\n";
		return false;
	}

	glClearColor(0.2f, 0.3f, 0, 1.0f);
	return true;
}

inline void initializeShaders() {
	testShader = new Shader("./testShader.vert", "./testShader.frag");
}

void framebuffer_size_callback(GLFWwindow* window, int w, int h) {
	glViewport(0, 0, w, h);
}

inline GLFWwindow* createWindow(int x, int y) {
	GLFWwindow* window = glfwCreateWindow(x, y, "Test Window", NULL, NULL);
	if (!window)
		return nullptr;
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	return window;
}

void render() {
	TestTriangle tri;
	tri.generateTriangle();
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		testShader->use();
		glBindVertexArray(tri.VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void cleanUp() {
	delete testShader;
}

int main(int argc, char * argv[]) {
	// Initialize window settings
	initializeGLFWSettings();
	// Create a window
	window = createWindow(800, 600);
	if (!window) {
		std::cerr << "Failed to create window\n";
		glfwTerminate();
		return -1;
	}
	if (!initializeGLSettings()) {
		std::cerr << "Failed to initialize GLAD\n";
		return -1;
	}
	initializeShaders();
	// Main window rendering loop
	render();
	// Do cleanup
	glfwTerminate();
	cleanUp();

	return 0;
}