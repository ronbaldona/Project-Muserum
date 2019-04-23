#define MAINPROGRAM
#include "variables.h"

#include <iostream>
#include "Display.h"

extern enum lightType;

inline bool initializeGLSettings() {
	// Load OpenGL function ptrs
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD\n";
		return false;
	}
	// Set depth test for 3D objects
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	// Set polygon drawing mode to fill front and back of 3d object
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	// Turn off backface culling for now
	glDisable(GL_CULL_FACE);
	glClearColor(0, 0, 1.0f, 0);
	return true;
}

void setUpCallBacks() {
	// Set up callbacks
	glfwSetKeyCallback(window, Display::key_callback);
	glfwSetFramebufferSizeCallback(window, Display::resize_callback);
}


// Replace with window rendering
void render() {
	teapot = new Model("teapot.obj");
	light = new Light(DIRECTIONAL, glm::normalize(-vec3(0.5f, 0.5f, 0.5f)), vec3(1.0f, 1.0f, 1.0f));
	testShader->use();
	teapot->setMaterials(vec4(0.24725f, 0.2245f, 0.0645f, 1.0f),
						 vec4(0.34615f, 0.3143f, 0.0903f, 1.0f),
						 vec4(0.797357f, 0.723991f, 0.208006f, 1.0f),
						 vec4(0.0f, 0.0f, 0.0f, 0.0f),
						 83.2f, *testShader);
	light->sendLightInfo(*testShader);
	testShader->setVec3("eyeloc", camPos);
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		Display::idle_callback();
		testShader->setMat4("modelview", viewMat * teapot->model);
		testShader->setMat4("projection", projMat);
		testShader->setMat4("model", teapot->model);
		teapot->Draw(*testShader);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}


int main(int argc, char * argv[]) {
	// Create a window
	// Initialize window settings
	Display::setupGLFW();
	window = Display::createWindow(width, height);
	if (!window) {
		std::cerr << "Failed to create window\n";
		glfwTerminate();
		return -1;
	}
	setUpCallBacks();
	if (!initializeGLSettings()) {
		std::cerr << "Failed to initialize GLAD\n";
		return -1;
	}
	Display::resize_callback(window, width, height);
	Display::initShaderPrograms();
	// Main window rendering loop
	render();
	Display::cleanUp();

	return 0;
}