#pragma once

#include "Shader.h"

using glm::vec3;
using glm::vec4;

enum lightType { DIRECTIONAL = 0, PNT = 1, SPOTLIGHT = 2 };

class Light {
	// Model lightModel;
	lightType type;
	vec4 color, position, direction;
	vec3 attenuation;

public:
	float phi;
	// Directional
	Light(lightType lt, vec4 dir, vec4 col) {
		type = lt;
		direction = -dir;
		color = col;
	}
	// Point
	Light(lightType lt, vec4 pos, vec3 atten, vec4 col) {
		type = lt;
		position = pos;
		attenuation = atten;
		color = col;
	}
	// Spotlight
	Light(lightType lt, vec4 pos, vec4 dir, vec3 atten, vec4 col, float angle) {
		type = lt;
		position = pos;
		direction = -dir;
		attenuation = atten;
		color = col;
		phi = glm::radians(angle);
	}

	void sendLightInfo(Shader &shader);

};