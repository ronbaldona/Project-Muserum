#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

typedef glm::vec2 vec2;
typedef glm::vec3 vec3;
typedef glm::vec4 vec4;
typedef glm::mat3 mat3;
typedef glm::mat4 mat4;

class GLDebugHelp {
public:
	// Just print the info of the string
	static void printVec2(const vec2 v);
	static void printVec3(const vec3 v);
	static void printVec4(const vec4 v);
	static void printMat3(const mat3 m, bool transpose);
	static void printMat4(const mat4 m, bool transpose);

	// Add a small description to the string
	static void printVec2(const std::string description, vec2 v);
	static void printVec3(const std::string description, const vec3 v);
	static void printVec4(const std::string description, const vec4 v);
	static void printMat3(const std::string description, const mat3 m, bool transpose);
	static void printMat4(const std::string description, const mat4 m, bool transpose);
};
