#include "Display.h"


GLFWwindow* Display::createWindow(int x, int y) {
	//glfwInit();
	GLFWwindow* window = glfwCreateWindow(x, y, "Test Window", NULL, NULL);
	if (!window)
		return nullptr;
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, Display::resize_callback);
	//resize_callback(window, x, y);
	return window;
}
void Display::setupGLFW() {
	glfwInit();
	// We will be working with OpenGL 3.3 Core
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Display::init_objects() {

}

void Display::initShaderPrograms() {
	testShader = new Shader("./testShader.vert", "./testShader.frag");

}

void Display::cleanUp() {
	delete testShader;

	glfwTerminate();
}

void Display::resize_callback(GLFWwindow* window, int w, int h) {
	width = w;
	height = h;
	glViewport(0, 0, width, height);
	if (height > 0) {
		projMat = glm::perspective(glm::radians(fovY), (float)width / (float)height, 0.1f, 1000.0f);
		viewMat = glm::lookAt(camPos, camLookAt, camUp);
	}
}

void Display::idle_callback() {

}

void Display::display_callback(GLFWwindow* window) {
	// Clear color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUniform4fv(glGetUniformLocation(testShader->ID, "projection"), 1, &projMat[0][0]);

	// Render object here

}

void Display::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	// Check for a key press
	if (action == GLFW_PRESS || action == GLFW_REPEAT)
	{
		// Check if escape was pressed
		if (key == GLFW_KEY_ESCAPE)
		{
			// Close the window. This causes the program to also terminate.
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
	}
}

void Display::mouse_callback(GLFWwindow* window, int button, int action, int mods) {

}

void Display::cursor_callback(GLFWwindow* window, double xpos, double ypos) {

}

void Display::scroll_callback(GLFWwindow* window, double xoffeset, double yoffset) {

}
