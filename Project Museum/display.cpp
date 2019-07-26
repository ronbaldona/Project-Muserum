#include "Display.h"
#include "GLDebugHelp.h"

// State definitions
const bool ROTATE_MODE_TRACKBALL = true;
const bool ROTATE_MODE_LOOKAROUND = false;

// State variables
bool doRotate = false;
bool doRotateLeft = true;
bool rotateMode = ROTATE_MODE_TRACKBALL;
bool lmbPressed = false;

// Variables for trackball rotation
vec3 oldCursorPosProjected;

// List of 3D objects
vector<Light*> lightList;
vector<Model*> objList;

short whichLight = PNT;

/*---------- HELPER FUNCTIONS ----------*/
inline vec3 projectToViewportHemisphere(double xPos, double yPos) {
	vec3 toRet;
	toRet.x = (float)(2 * xPos - width) / width;
	toRet.y = (float)(height - 2 * yPos) / height;
	
	// Point lies outside unit circle. Project it to the nearest point on the circle
	float d = (toRet.x * toRet.x) + (toRet.y * toRet.y);
	if (d > 1.0f) {
		toRet.z = 0;
		return normalize(toRet);
	}

	toRet.z = sqrt(1.0f - d);

	return toRet;
}

inline double getMagnitude(vec3 v) { return sqrt(v.x * v.x + v.y * v.y + v.z * v.z); }

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
	cout << "Rotate Mode Change: m\n";
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
	pntLight->translate(-0.1f, 0.7f, 1.0f);

	float angle;
	vec3 axis;
	spotlight->translate(-1.0f, 1.0f, 1.0f);
	Model::getAxisAngle(angle, axis, vec3(0, 1.0f, 0), spotlight->getDirection());
	spotlight->rotate(angle, axis);

	// Init shaders
	phongShader = new Shader("./phongShader.vert", "./phongShader.frag");
}

void Display::cleanUp() {
	delete phongShader;
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
		// REWRITE TO SWITCH STATEMENT LATER
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
		else if (key == GLFW_KEY_M) {
			rotateMode = !rotateMode;
			if (rotateMode == ROTATE_MODE_LOOKAROUND) {
				cout << "Mouse control of camera ON. Trackball control OFF\n";
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			}
			else {
				cout << "Mouse control of camera OFF. Trackball control ON\n";
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			}

		}
		// Light settings
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
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		// Set button pressed down state to true
		// Get cursor position of press and set it to oldpos
		// Project it to hemisphere
		double cursorXPos, cursorYPos;
		glfwGetCursorPos(window, &cursorXPos, &cursorYPos);
		oldCursorPosProjected = projectToViewportHemisphere(cursorXPos, cursorYPos);
		lmbPressed = true;
		cout << "LMB pressed\n";
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		cout << "LMB released\n";
		lmbPressed = false;
	}

}

void Display::cursor_callback(GLFWwindow* window, double xpos, double ypos) {
	// Get current position of the cursor
	// Project it to hemisphere
	// Get angle and axis of rotation
	// Rotate the object
	if (lmbPressed) {
		vec3 currentPosProjected = projectToViewportHemisphere(xpos, ypos);
		vec3 axisOfRotation = glm::cross(oldCursorPosProjected, currentPosProjected);
		double angleOfRotation = asin(getMagnitude(axisOfRotation)) * (180.0f / PI);

		if (glm::length(axisOfRotation) > 0.0000001f)
			axisOfRotation = glm::normalize(axisOfRotation);
		teapot->rotate(angleOfRotation, axisOfRotation);

		/*
		GLDebugHelp::printVec3("Old Cursor Position", oldCursorPosProjected);
		GLDebugHelp::printVec3("Current Cursor Position", currentPosProjected);
		GLDebugHelp::printVec3("Axis of Rotation", axisOfRotation);
		cout << endl;
		*/
	}
}

void Display::scroll_callback(GLFWwindow* window, double xoffeset, double yoffset) {

}
