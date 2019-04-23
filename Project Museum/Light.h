#pragma once

#include "Shader.h"

using glm::vec3;
using glm::vec4;

enum lightType { DIRECTIONAL = 0, PNT = 1, SPOTLIGHT = 2 };

class Light {
	lightType type;
	vec3 color, position, direction, attenuation;
	float phi;

public:
	// Directional
	Light(lightType lt, vec3 dir, vec3 col) {
		type = lt;
		direction = -dir;
		color = col;
	}
	// Point
	Light(lightType lt, vec3 pos, vec3 atten, vec3 col) {
		type = lt;
		position = pos;
		attenuation = atten;
		color = col;
	}
	// Spotlight
	Light(lightType lt, vec3 pos, vec3 dir, vec3 atten, vec3 col, float angle) {
		type = lt;
		position = pos;
		direction = -dir;
		attenuation = atten;
		color = col;
		phi = angle;
	}

	void sendLightInfo(Shader &shader);

};