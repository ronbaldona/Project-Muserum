#include "Light.h"

void Light::sendLightInfo(Shader &shader) {
	if (type == DIRECTIONAL) {
		shader.setInt("type", 0);
		shader.setVec3("direction", direction);
		shader.setVec3("color", color);
	}
	else if (type == PNT) {
		shader.setInt("type", 1);
		shader.setVec3("position", position);
		shader.setVec3("attenuation", attenuation);
		shader.setVec3("color", color);

	}
	else {
		shader.setInt("type", 2);
		shader.setVec3("position", position);
		shader.setVec3("direction", direction);
		shader.setVec3("attenuation", attenuation);
		shader.setVec3("color", color);
		shader.setFloat("phi", phi);
	}
}

