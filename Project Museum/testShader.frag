# version 330 core

in vec3 myNormal;
in vec3 myEyeLoc;
in vec4 myVertex; 

// You will certainly need this matrix for your lighting calculations
uniform mat4 modelview;

// This first defined output of type vec4 will be the fragment color
out vec4 fragColor;

void main (void) 
{
	fragColor = vec4(myNormal, 1.0f);
	//fragColor = vec4(1.0f, 0, 0, 1.0f);
}
