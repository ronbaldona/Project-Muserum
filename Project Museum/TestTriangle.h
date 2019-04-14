#pragma once
#include "variables.h"

float vertices[] = {
	0.5f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
	-0.5f, 0.5f, 0.0f

};
unsigned int indices[] = {
	0, 1, 3,
	1, 2, 3
};

class TestTriangle {
public:
	unsigned int VAO, VBO, EBO;

	TestTriangle() {}
	~TestTriangle() {}

	void generateTriangle() {
		// Generate the buffer and vertex array
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		// Initialization of the triangle (done once unless your object frequently changes)
		glBindVertexArray(VAO);
		// Bind the buffer to work on
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		// Allocate memory and read the vertices into it
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		// Do the same for the Element buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		// Tell OpenGL how to read the VBO data
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);



		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

	}
};