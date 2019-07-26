# version 330 core
// INPUTS FROM VERTEX SHADER
in vec3 myNormal;
in vec4 myVertex;

// Light info
struct Light {
	int type;
	vec4 color;
	vec4 position;
	vec4 direction;
	vec3 attenuation;
	float phi, outerCutoff, innerCutoff;
};
uniform Light light;
const int DIRECTIONAL = 0;
const int POINT = 1;
const int SPOTLIGHT = 2;

// Object material info
struct Material {
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec4 emission;
	float shininess;
};
uniform Material material;

// Use this to transform light to object space
uniform mat4 modelview;
uniform mat4 view;

// Other constants
uniform bool isLight;
const float PI = 3.14159265359f;

// This first defined output of type vec4 will be the fragment color
out vec4 fragColor;

// Calculates Blinn-Phong lighting vals
vec4 computeLight(vec3 eyePos, vec3 vertPos, vec3 lightDir, vec3 normal) {
	// Diffuse
	float nDotL = dot(normal, lightDir);
	vec4 lambertian = (light.color * material.diffuse * max(nDotL, 0));

	// Blinn-Phong Specular
	vec3 fragPosToEye = normalize(eyePos - vertPos);
	float nDotH = dot(normal, normalize(lightDir + fragPosToEye));
	vec4 blinnPhong = light.color * material.specular * 
					  ((8 + material.shininess) / (8 * PI)) * pow(max(nDotH, 0), material.shininess);

	return lambertian + blinnPhong;
}

void main (void) 
{
	if (isLight) {
		//fragColor = vec4(normalize(myNormal), 1.0f);
		fragColor = light.color;
		return;
	}
	// Note that the calculations are done in view space
	vec3 vertPos = myVertex.xyz / myVertex.w;
	vec3 eyePos = vec3(0, 0, 0);
	vec3 normal = normalize(myNormal);
	vec4 finalColor = vec4(0, 0, 0, 0);
	if (light.type == DIRECTIONAL) {
		vec3 transfDir = vec3(view * light.direction);
		finalColor = computeLight(eyePos, vertPos, normalize(transfDir), normal);
	}
	// Point light and spotlight
	else {
		float attenuationConst;
		vec4 transfLightPos = view * light.position;
		vec3 vecToLight = (transfLightPos.xyz / transfLightPos.w) - vertPos;
		float distToLight = length(vecToLight);
		attenuationConst = 1.0f / (light.attenuation[0] + 
								   light.attenuation[1] * distToLight +
								   light.attenuation[2] * distToLight * distToLight);
		vecToLight = normalize(vecToLight);

		// Spotlight lighting
		if (light.type == SPOTLIGHT) {
			vec3 spotDir = normalize(vec3(view * light.direction));
			float theta = dot(vecToLight, spotDir);
			// Light lies within the spotlight's lighting
			if (light.outerCutoff < theta) {
				float spotIntensity = (theta - light.outerCutoff) / (light.innerCutoff - light.outerCutoff);
				spotIntensity = clamp(spotIntensity, 0.0f, 1.0f);
				finalColor = spotIntensity * attenuationConst * computeLight(eyePos, vertPos, vecToLight, normal);
			}
		}
		// Point light based lighting
		else 
			finalColor = attenuationConst * computeLight(eyePos, vertPos, vecToLight, normal);
	}
	fragColor = material.ambient + material.emission + finalColor;
}
