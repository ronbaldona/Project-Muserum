#include "Light.h"

void Light::sendLightInfo(Shader& shader) {
	if (type == DIRECTIONAL) {
		shader.setInt("light.type", 0);
		shader.setVec4("light.color", color);
		shader.setVec4("light.position", position);
		shader.setVec4("light.direction", direction);
		shader.setVec3("light.attenuation", attenuation);
		shader.setFloat("light.phi", phi);
		shader.setFloat("light.innerCutoff", innerCutoff);
		shader.setFloat("light.outerCutoff", outerCutoff);
	}
	else if (type == PNT) {
		shader.setInt("light.type", 1);
		shader.setVec4("light.color", color);
		shader.setVec4("light.position", position);
		shader.setVec4("light.direction", direction);
		shader.setVec3("light.attenuation", attenuation);
		shader.setFloat("light.phi", phi);
		shader.setFloat("light.innerCutoff", innerCutoff);
		shader.setFloat("light.outerCutoff", outerCutoff);
	}
	// Spotlight info
	else {
		shader.setInt("light.type", 2);
		shader.setVec4("light.color", color);
		shader.setVec4("light.position", position);
		shader.setVec4("light.direction", direction);
		shader.setVec3("light.attenuation", attenuation);
		shader.setFloat("light.phi", phi);
		shader.setFloat("light.innerCutoff", innerCutoff);
		shader.setFloat("light.outerCutoff", outerCutoff);
	}
}

void Light::setUniformMaterial(Shader shader) const {
	shader.setVec4("color", color);
	shader.setBool("isLight", true);
}