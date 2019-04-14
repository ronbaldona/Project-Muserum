#pragma once

#include <iostream>
#include <string>
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

using glm::vec2;
using glm::vec3;
using namespace::std;

struct Vertex {
	vec3 Pos;
	vec3 Normal;
	vec2 texCoords;
};

struct Texture {
	unsigned int id;
	std::string type;
};

class Mesh {
	// Objects for rendering
	unsigned int VAO, VBO, EBO;
	void setupMesh();

public:
	// Mesh data
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;
	// Functions
	Mesh() {}
	~Mesh() {}
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture>textures);
	void Draw(Shader shaderProg);

};
