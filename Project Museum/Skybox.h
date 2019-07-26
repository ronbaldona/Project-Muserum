#pragma once
#include "Model.h"
class Skybox : public Model
{
	GLfloat cubeVerts;
	GLuint cubeIndices;

	GLuint VAO, VBO, EBO;

	Skybox() {
		loadModel();
	}
	~Skybox() {}
	
	void loadModel();


public:
	void setUniformMaterial(Shader shader) const;
	void Draw(Shader shader, const mat4& view, const mat4& projection);
};

