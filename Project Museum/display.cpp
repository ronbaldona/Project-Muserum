#include "Display.h"

// State variables
bool doRotate = false;
bool doRotateLeft = false;


GLFWwindow* Display::createWindow(int x, int y) {
	GLFWwindow* window = glfwCreateWindow(x, y, "Test Window", NULL, NULL);
	if (!window)
		return nullptr;
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, Display::resize_callback);
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
	// Init objects + properties
	teapot = new Model("teapot.obj");
	teapot->setMaterials(vec4(0.24725f, 0.2245f, 0.0645f, 1.0f),
						 vec4(0.34615f, 0.3143f, 0.0903f, 1.0f),
						 vec4(0.797357f, 0.723991f, 0.208006f, 1.0f),
						 vec4(0.0f, 0.0f, 0.0f, 0.0f),
						 83.2f);
	
	// Init lights and their properties
	dirLight = new Light(DIRECTIONAL, 
		                 glm::normalize(vec4(-0.5f, -0.5f, -0.5f, 0)), 
		                 vec4(1.0f, 1.0f, 1.0f, 1.0f));
	pntLight = new Light(PNT, 
						 vec4(-0.1f, 0.7f, 1.0f, 1.0f), 
						 vec3(1.0f, 0.5f, 0.1f), 
						 vec4(0.1f, 0.2f, 0.8f, 1.0f));
	spotlight = new Light(SPOTLIGHT, 
						 vec4(-1.0f, 1.0f, 1.0f, 1.0f), 
						 glm::normalize(vec4(1.0f, -1.0f, -1.0f, 0)),
						 vec3(1.0f, 0.5f, 0.1f),
						 vec4(1.0f, 1.0f, 1.0f, 1.0f),
						 15.0f);

	// Init shader
	testShader = new Shader("./testShader.vert", "./testShader.frag");
}

void Display::cleanUp() {
	delete testShader;
	delete teapot;

	delete dirLight, pntLight, spotlight;

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
	if (doRotate) {
		if (doRotateLeft)
			teapot->rotate(1.0f, vec3(0, 1.0f, 0));
		// Rotate up
		else
			teapot->rotate(1.0f, vec3(1.0f, 0, 0));

	}
}

void Display::display_callback(GLFWwindow* window) {
	testShader->use();
	teapot->sendMaterialInfo(*testShader);
	//dirLight->sendLightInfo(*testShader);
	//pntLight->sendLightInfo(*testShader);
	spotlight->sendLightInfo(*testShader);
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		Display::idle_callback();
		testShader->setMat4("modelview", viewMat * teapot->model);
		testShader->setMat4("view", viewMat);
		testShader->setMat4("projection", projMat);
		//testShader->setMat4("model", teapot->model);
		testShader->setVec3("eyeloc", camPos);
		teapot->Draw(*testShader);
		//cout << spotlight->phi << endl;

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
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
		// Turn on idle rotation
		else if (key == GLFW_KEY_R) {
			doRotate = !doRotate;
		}
		// Choose rotate direction
		else if (key == GLFW_KEY_L) {
			doRotateLeft = !doRotateLeft;
		}
	}
}

void Display::mouse_callback(GLFWwindow* window, int button, int action, int mods) {

}

void Display::cursor_callback(GLFWwindow* window, double xpos, double ypos) {

}

void Display::scroll_callback(GLFWwindow* window, double xoffeset, double yoffset) {

}
