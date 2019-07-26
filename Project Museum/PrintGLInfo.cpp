#include "GLdebugHelp.h"

#include <iostream>
#include <cstdio>

using namespace std;

void GLDebugHelp::printVec2(const vec2 v) {
	printf("x:%f, y:%f\n", v.x, v.y);
}
void GLDebugHelp::printVec3(const vec3 v) {
	printf("x:%f, y:%f, z:%f\n", v.x, v.y, v.z);
}
void GLDebugHelp::printVec4(const vec4 v) {
	printf("x:%f, y:%f\n, z:%f, w:%f\n", v.x, v.y, v.z, v.w);
}
void GLDebugHelp::printMat3(const mat3 m, bool transpose) {
	if (transpose) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				cout << m[i][j] << ", ";
			}
			cout << endl;
		}
	}
	else {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				cout << m[j][i] << ", ";
			}
			cout << endl;
		}
	}
}
void GLDebugHelp::printMat4(const mat4 m, bool transpose) {
	if (transpose) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				cout << m[i][j] << ", ";
			}
			cout << endl;
		}
	}
	else {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				cout << m[j][i] << ", ";
			}
			cout << endl;
		}
	}
}

void GLDebugHelp::printVec2(const std::string description, vec2 v) {
	cout << description << endl;
	printVec2(v);
}
void GLDebugHelp::printVec3(const std::string description, const vec3 v) {
	cout << description << endl;
	printVec3(v);
}
void GLDebugHelp::printVec4(const std::string description, const vec4 v) {
	cout << description << endl;
	printVec4(v);
}
void GLDebugHelp::printMat3(const std::string description, const mat3 m, bool transpose) {
	cout << description << endl;
	printMat3(m, transpose);
}
void GLDebugHelp::printMat4(const std::string description, const mat4 m, bool transpose) {
	cout << description << endl;
	printMat4(m, transpose);
}

