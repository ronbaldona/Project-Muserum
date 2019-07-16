#include "Display.h"

// State variables
bool doRotate = false;
bool doRotateLeft = true;

// List of 3D objects
vector<Light*> lightList;
vector<Model*> objList;

short whichLight = 1;


GLFWwindow* Display::createWindow(int x, int y) {
	GLFWwindow* window = glfwCreateWindow(x, y, "Test Window", NULL, NULL);
	if (!window)
		return nullptr;
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, Display::resize_callback);
	return window;
}

// Set up GLFW for creating windows and OpenGL contexts
void Display::setupGLFW() {
	glfwInit();
	// We will be working with OpenGL 3.3 Core
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}
void Display::helpMessage() {
	cout << "Controls\n";
	cout << "------------------------------\n";
	cout << "Rotate: r\n";
	cout << "Directional Light: 1\n";
	cout << "Point Light: 2\n";
	cout << "Spotlight: 3\n";
	cout << "Help: h\n";
	cout << "------------------------------\n\n";
}

void Display::init_objects() {
	// Init objects + properties
	teapot = new Model("teapot.obj");
	teapot->setMaterialVal(vec4(0.24725f, 0.2245f, 0.0645f, 1.0f),		// Ambient
						   vec4(0.34615f, 0.3143f, 0.0903f, 1.0f),		// Diffuse
						   vec4(0.797357f, 0.723991f, 0.208006f, 1.0f),	// Specular
						   vec4(0.0f, 0.0f, 0.0f, 0.0f),				// Emission
						   83.2f);										// Shininess
	
	// Initialize lights
	dirLight = new Light(DIRECTIONAL,									// Type
		                 glm::normalize(vec4(-0.5f, -0.5f, -0.5f, 0)),	// Direction
		                 vec4(1.0f, 1.0f, 1.0f, 1.0f));					// Color
	pntLight = new Light(PNT,							// Type
						 vec4(-0.1f, 0.7f, 1.0f, 1.0f),	// Position
						 vec3(1.0f, 0.5f, 0.1f),		// Attenuation
						 vec4(0.1f, 0.2f, 0.8f, 1.0f),	// Color
						 "./Light/sphere.obj");			// Path to model
	spotlight = new Light(SPOTLIGHT,									// Type
						  vec4(-1.0f, 1.0f, 1.0f, 1.0f),				// Position
						  glm::normalize(vec4(1.0f, -1.0f, -1.0f, 0)),	// Direction
						  vec3(1.0f, 0.5f, 0.1f),						// Attenuation
						  vec4(1.0f, 1.0f, 1.0f, 1.0f),					// Color
						  20.0f,										// Outer Angle
						  15.0f,										// Inner Angle
						  "./Light/cone.obj");							// Path to model
	//pntLight->translate(-0.1f, 0.7f, 1.0f);
	spotlight->translate(-1.0f, 1.0f, 1.0f);

	// Init shaders
	phongShader = new Shader("./phongShader.vert", "./phongShader.frag");
	lightShader = new Shader("./lightShader.vert", "./lightShader.frag");
}

void Display::cleanUp() {
	delete phongShader, lightShader;
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
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		Display::idle_callback();

		// Draw the lights
		phongShader->use();
		switch (whichLight) {
		case DIRECTIONAL:
			break;
		case PNT:
			pntLight->Draw(*phongShader, viewMat, projMat);
			break;
		case SPOTLIGHT:
			spotlight->Draw(*phongShader, viewMat, projMat);
			break;
		}

		// Send the right lighting info, and then draw the rest of the scene
		phongShader->setBool("isLight", false);
		switch (whichLight) {
		case DIRECTIONAL:
			dirLight->sendLightInfo(*phongShader);
			break;
		case PNT:
			pntLight->sendLightInfo(*phongShader);
			break;
		case SPOTLIGHT:
			spotlight->sendLightInfo(*phongShader);
			break;
		}
		teapot->Draw(*phongShader, viewMat, projMat);
		
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
		else if (key == GLFW_KEY_1) {
			cout << "Switched to directional light\n";
			whichLight = DIRECTIONAL;
		}
		else if (key == GLFW_KEY_2) {
			cout << "Switched to point light\n";
			whichLight = PNT;
		}
		else if (key == GLFW_KEY_3) {
			cout << "Switched to spotlight\n";
			whichLight = SPOTLIGHT;
		}
		else if (key == GLFW_KEY_H) {
			helpMessage();
		}
	
	}
}

void Display::mouse_callback(GLFWwindow* window, int button, int action, int mods) {

}

void Display::cursor_callback(GLFWwindow* window, double xpos, double ypos) {

}

void Display::scroll_callback(GLFWwindow* window, double xoffeset, double yoffset) {

}
