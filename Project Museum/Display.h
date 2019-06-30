#pragma once

#include "variables.h"

#include <iostream>

class Display {
public:
	static GLFWwindow* createWindow(int x, int y);
	static void helpMessage();
	static void setupGLFW();
	static void init_objects();
	static void cleanUp();
	static void resize_callback(GLFWwindow* window, int w, int h);
	static void idle_callback();
	static void display_callback(GLFWwindow*);	// Render objects here
	static void key_callback(GLFWwindow*, int key, int scancode, int action, int mods);
	static void mouse_callback(GLFWwindow* window, int button, int action, int mods);
	static void cursor_callback(GLFWwindow* window, double xpos, double ypos);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
};
