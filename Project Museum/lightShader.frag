# version 330 core
in vec3 myNormal;

uniform vec4 color;

// This first defined output of type vec4 will be the fragment color
out vec4 fragColor;
void main (void) 
{
	//fragColor = vec4(normalize(myNormal), 1.0f);
	fragColor = color;
}