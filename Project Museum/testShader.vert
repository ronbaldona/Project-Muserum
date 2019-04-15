#version 330 core

// Vertex shader location
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform mat4 modelview;
uniform mat4 projection;
uniform vec3 eyeloc;

// Additional outputs
out vec3 myNormal;
out vec3 myEyeLoc;
out vec4 myVertex;

void main() {
	gl_Position = projection * modelview * vec4(position, 1.0);

	// Transform the normal
	myNormal = mat3(transpose(inverse(modelview))) * normal;
	myVertex = modelview * vec4(position, 1.0f);
	myEyeLoc = eyeloc;
}