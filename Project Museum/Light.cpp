#include "Light.h"

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
	else {
		shader.setInt("light.type", 2);
		shader.setVec4("light.position", position);
		shader.setVec4("light.direction", direction);
		shader.setVec3("light.attenuation", attenuation);
		shader.setVec4("light.color", color);
		shader.setFloat("light.phi", glm::cos(phi));
	}
}

