#include "Display.h"

// State variables
bool doRotate = false;
bool doRotateLeft = true;

// List of 3D objects
vector<Light*> lightList;
vector<Model*> objList;

short whichLight = 1;

/**************** MISCELLANEOUS HELPER FUNCTIONS ******************/
/*
void renderObjects() {

}

void renderLights() {

}
*/

/**************** MISCELLANEOUS HELPER FUNCTIONS ******************/

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
void Display::helpMessage() {
	cout << "Controls\n";
	cout << "------------------------------\n";
	cout << "Rotate: r\n";
	cout << "Help: h\n";
	cout << "------------------------------\n\n";
}

void Display::init_objects() {
	// Init objects + properties
	teapot = new Model("teapot.obj");
	teapot->setMaterials(vec4(0.24725f, 0.2245f, 0.0645f, 1.0f),
						 vec4(0.34615f, 0.3143f, 0.0903f, 1.0f),
						 vec4(0.797357f, 0.723991f, 0.208006f, 1.0f),
						 vec4(0.0f, 0.0f, 0.0f, 0.0f),
						 83.2f);
	pntLgtModel = new Model("./Light/sphere.obj");
	sptLgtModel = new Model("./Light/cone.obj");
	
	// Init lights and their properties
	dirLight = new Light(DIRECTIONAL, 
		                 glm::normalize(vec4(-0.5f, -0.5f, -0.5f, 0)), 
		                 vec4(1.0f, 1.0f, 1.0f, 1.0f));
	pntLight = new Light(PNT, 
						 vec4(-0.1f, 0.7f, 1.0f, 1.0f), 
						 vec3(1.0f, 0.5f, 0.1f), 
						 vec4(0.1f, 0.2f, 0.8f, 1.0f),
						 pntLgtModel);
	spotlight = new Light(SPOTLIGHT,
						  vec4(-1.0f, 1.0f, 1.0f, 1.0f),
						  glm::normalize(vec4(1.0f, -1.0f, -1.0f, 0)),
						  vec3(1.0f, 0.5f, 0.1f), 
						  vec4(1.0f, 1.0f, 1.0f, 1.0f), 
						  20.0f, 15.0f,
						  sptLgtModel);

	// Init shaders
	phongShader = new Shader("./phongShader.vert", "./phongShader.frag");
	lightShader = new Shader("./lightShader.vert", "./lightShader.frag");
}

void Display::cleanUp() {
	delete phongShader, lightShader;
	delete teapot, pntLgtModel, sptLgtModel;
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
		//lightShader->use();
		glUseProgram(lightShader->ID);
		/*
		switch (whichLight) {
		case DIRECTIONAL:
			dirLight->draw(*lightShader, viewMat, projMat);
			break;
		case PNT:
			pntLight->draw(*lightShader, viewMat, projMat);
			break;
		case SPOTLIGHT:
			spotlight->draw(*lightShader, viewMat, projMat);
			break;
		}
		*/
		spotlight->draw(*lightShader, viewMat, projMat);

		// Send the right lighting info, and then draw the rest of the scene
		
		//phongShader->use();
		glUseProgram(phongShader->ID);
		teapot->Draw(*phongShader, viewMat, projMat);
		
		/*
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
		teapot->rotate(-30.0f, vec3(0, 1.0f, 0));
		//teapot->Draw(*phongShader, viewMat, projMat);
		teapot->rotate(30.0f, vec3(0, 1.0f, 0));
		*/
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
