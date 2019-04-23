# version 330 core

in vec3 myNormal;
in vec3 myVertex;
in vec3 myEyeLoc;

uniform int type;
uniform vec3 color, position, direction, attenuation;
uniform float phi;

uniform vec4 ambient;
uniform vec4 diffuse;
uniform vec4 specular;
uniform vec4 emission;
uniform float shininess;

const int DIRECTIONAL = 0;
const int POINT = 1;
const int SPOTLIGHT = 2;
const float PI = 3.14159265359f;

// This first defined output of type vec4 will be the fragment color
out vec4 fragColor;

vec4 computeLight(vec3 lightDir, vec3 normal) {
	// Diffuse
	float nDotL = dot(normal, lightDir);
	vec4 lambertian = (vec4(color, 1.0f) * diffuse * max(nDotL, 0));

	// Blinn-Phong Specular
	vec3 fragPosToEye = normalize(myEyeLoc - myVertex);
	float nDotH = dot(normal, normalize(lightDir + fragPosToEye));
	vec4 blinnPhong = vec4(color, 1.0f) * specular *  ((8 + shininess) / (8 * PI)) * pow(max(nDotH, 0), shininess);

	return lambertian + blinnPhong;
}

void main (void) 
{
	vec3 lightDir;
	vec3 normal = normalize(myNormal);
	if (type == DIRECTIONAL) {
		lightDir = normalize(direction);
	}
	else if (type == POINT) {
		lightDir = normalize(position - myVertex);
	}
	else {
		lightDir = direction;
	}
	
	fragColor = computeLight(lightDir, normal);
	//fragColor = vec4(myNormal, 1.0f);
}
