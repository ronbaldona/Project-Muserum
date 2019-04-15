#define MAINPROGRAM
#include "variables.h"

#include <iostream>
#include "Display.h"
#include "TestTriangle.h"

inline bool initializeGLSettings() {
	// Load OpenGL function ptrs
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD\n";
		return false;
	}
	// Set depth test for 3D objects
	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LEQUAL);
	// Set polygon drawing mode to fill front and back of 3d object
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	// Turn off backface culling for now
	glDisable(GL_CULL_FACE);
	glClearColor(0, 0, 0, 0);
	return true;
}

void setUpCallBacks() {
	// Set up callbacks
	glfwSetKeyCallback(window, Display::key_callback);
	glfwSetFramebufferSizeCallback(window, Display::resize_callback);
}


// Fix later
void render() {
	Model teapot = Model("teapot.obj");
	testShader->use();
	testShader->setMat4("modelview", viewMat);
	testShader->setMat4("projection", projMat);
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		teapot.Draw(*testShader);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}


int main(int argc, char * argv[]) {
	// Create a window
	// Initialize window settings
	Display::setupGLFW();
	window = Display::createWindow(width, height);
	setUpCallBacks();
	if (!window) {
		std::cerr << "Failed to create window\n";
		glfwTerminate();
		return -1;
	}
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