#pragma once
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
	unsigned int ID;

	Shader() {}
	~Shader() {}
	Shader(const GLchar* vertPath, const GLchar* fragPath);

	// Use the new shader program
	void use();

	// Shader state setter functions
	void setBool(const std::string &name, bool val) const;
	void setInt(const std::string &name, int val) const;
	void setFloat(const std::string &name, float val) const;
	void setMat3(const std::string &name, const glm::mat3 &val) const;
	void setMat4(const std::string &name, const glm::mat4 &val) const;
	void setVec3(const std::string &name, const glm::vec3 &val) const;
	void setVec4(const std::string &name, const glm::vec4 &val) const;


};