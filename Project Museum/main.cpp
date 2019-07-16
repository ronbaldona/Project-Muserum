#define MAINPROGRAM
#include "variables.h"

#include <iostream>
#include "Display.h"

enum lightType;

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
	//glDisable(GL_CULL_FACE);
	glClearColor(0, 0, 1.0f, 0);
	return true;
}

void setUpCallBacks() {
	// Set up callbacks
	glfwSetKeyCallback(window, Display::key_callback);
	glfwSetFramebufferSizeCallback(window, Display::resize_callback);
}

void print_info() {
	printf("Renderer used: %s\n", glGetString(GL_RENDERER));
	printf("OpenGL version supported %s\n", glGetString(GL_VERSION));

	//If the shading language symbol is defined
#ifdef GL_SHADING_LANGUAGE_VERSION
	std::printf("Supported GLSL version is %s.\n", (char*)glGetString(GL_SHADING_LANGUAGE_VERSION));
#endif
	printf("--------------------------------------------------\n\n");
}

int main(int argc, char * argv[]) {
	// Create a window
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
	// Print OpenGL info/rendering info
	print_info();
	
	// Remove this line below? Might be pointless
	Display::resize_callback(window, width, height);

	Display::init_objects();
	Display::helpMessage();
	// Main window rendering loop
	Display::display_callback(window);
	Display::cleanUp();

	return 0;
}