#pragma once

#include "Shader.h"
#include "Model.h"

using glm::vec3;
using glm::vec4;

enum lightType { DIRECTIONAL = 0, PNT = 1, SPOTLIGHT = 2 };

class Light {
	Model* lightModel;
	lightType type;
	vec4 color, position, direction;
	vec3 attenuation;
	float phi;
	float innerCutoff;
	float outerCutoff;

public:
	// Directional
	Light(lightType lt, vec4 dir, vec4 col) {
		lightModel = nullptr;
		type = lt;
		position = vec4(0, 0, 0, 0);
		direction = -dir;
		attenuation = vec3(1, 1, 1);
		color = col;
	}
	// Point
	Light(lightType lt, vec4 pos, vec3 atten, vec4 col, Model* model) {
		type = lt;
		position = pos;
		attenuation = atten;
		color = col;
		lightModel = model;
		lightModel->translate(position);
	}
	// Spotlight
	Light(lightType lt, vec4 pos, vec4 dir, vec3 atten, vec4 col, float outerAngle, float innerAngle, Model* model) {
		type = lt;
		position = pos;
		direction = -dir;
		attenuation = atten;
		color = col;
		outerCutoff = glm::cos(glm::radians(outerAngle));
		innerCutoff = glm::cos(glm::radians(innerAngle));
		lightModel = model;
		lightModel->translate(position);
	}

	void sendLightInfo(Shader &shader);
	void draw(Shader &shader);
	void draw(Shader& shader, const mat4& view, const mat4& projection);
};