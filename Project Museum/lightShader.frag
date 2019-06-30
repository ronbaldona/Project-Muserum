# version 330 core
in vec3 myNormal;
//in vec4 myVertex;

struct Material {
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec4 emission;
	float shininess;
};
uniform Material material;

// This first defined output of type vec4 will be the fragment color
out vec4 fragColor;
void main (void) 
{
	fragColor = vec4(normalize(myNormal), 1.0f);
}