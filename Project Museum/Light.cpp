#include "Light.h"

/******* HELPER FUNCTIONS ********/

/******* HELPER FUNCTIONS ********/


void Light::sendLightInfo(Shader &shader) {
	if (type == DIRECTIONAL) {
		shader.setInt("light.type", 0);
		shader.setVec4("light.direction", direction);
		shader.setVec4("light.color", color);
	}
	else if (type == PNT) {
		shader.setInt("light.type", 1);
		shader.setVec4("light.position", position);
		shader.setVec3("light.attenuation", attenuation);
		shader.setVec4("light.color", color);
	}
	// Spotlight info
	else {
		shader.setInt("light.type", 2);
		shader.setVec4("light.position", position);
		shader.setVec4("light.direction", direction);
		shader.setVec3("light.attenuation", attenuation);
		shader.setVec4("light.color", color);
		shader.setFloat("light.phi", phi);
		shader.setFloat("light.outerCutoff", outerCutoff);
		shader.setFloat("light.innerCutoff", innerCutoff);
	}
}

void Light::draw(Shader& shader) {
	switch (type) {
	case DIRECTIONAL:
		return;
	default:
		if (!lightModel) {
			cout << "ERROR: Light missing 3D obj!\n";
			return;
		}
		lightModel->Draw(shader);
		break;
	}
}

void Light::draw(Shader& shader, const mat4& view, const mat4& projection) {
	// Directional does not have object representation for now
	if (type == DIRECTIONAL)
		return;
	lightModel->setMaterials(vec4(0, 0, 0, 0),
							 vec4(0, 0, 0, 0),
							 vec4(0, 0, 0, 0),
							 vec4(0, 0, 0, 0),
							 0.0f);
	lightModel->Draw(shader, view, projection);
}