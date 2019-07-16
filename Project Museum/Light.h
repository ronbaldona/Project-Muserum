/* Class for lights that can have 3D object representations for debugging/visual aid purposes
 * By Ronald Allan Baldonado
 */
#pragma once
#include "Shader.h"
#include "Model.h"

using glm::vec3;
using glm::vec4;
enum lightType { DIRECTIONAL = 0, PNT = 1, SPOTLIGHT = 2 };

class Light : public Model {
	// PHONG LIGHT INFORMATION
	lightType type;
	vec4 color, position, direction;
	vec3 attenuation;
	float phi;
	float innerCutoff;
	float outerCutoff;

	inline void initTransformMat() {
		rotMat = mat4(1.0f);
		scaleMat = mat4(1.0f);
		transMat = mat4(1.0f);
	}

public:
	// Directional Light
	Light(lightType lt, vec4 dir, vec4 col) {
		type = lt;
		color = col;
		position = vec4(0, 0, 0, 0);
		direction = -dir;
		attenuation = vec3(1, 1, 1);
		phi = 0;
		innerCutoff = 0;
		outerCutoff = 0;
	}
	// Point
	Light(lightType lt, vec4 pos, vec3 atten, vec4 col, string modelPath) {
		type = lt;
		color = col;
		position = pos;
		direction = vec4(0, 0, 0, 0);
		attenuation = atten;
		phi = 0;
		innerCutoff = 0;
		outerCutoff = 0;
		loadModel(modelPath);

		initTransformMat();
	}
	// Spotlight
	Light(lightType lt, vec4 pos, vec4 dir, vec3 atten, vec4 col, float outerAngle, float innerAngle, string modelPath) {
		type = lt;
		color = col;
		position = pos;
		direction = -dir;
		attenuation = atten;
		// WHAT DOES PHI DO?
		phi = 0;
		outerCutoff = glm::cos(glm::radians(outerAngle));
		innerCutoff = glm::cos(glm::radians(innerAngle));
		loadModel(modelPath);

		initTransformMat();
	}
	~Light() {}
	
	void sendLightInfo(Shader& shader);
	
	// Functions to override
	void setUniformMaterial(Shader shader) const override;
};