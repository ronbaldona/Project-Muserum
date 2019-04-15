#include "Shader.h"
const int CHARBUFSIZ = 512;

using glm::vec3;
using glm::vec4;
using glm::mat3;
using glm::mat4;
using namespace std;

char* readShaderFile(const GLchar* fileName) {
	string fileString;
	ifstream shaderFile;
	stringstream shaderStream;
	const char * shaderCode;
	char * toRet;

	shaderFile.exceptions(ifstream::failbit | ifstream::badbit);
	try {
		shaderFile.open(fileName);
		// Read file
		shaderStream << shaderFile.rdbuf();
		// Close file
		shaderFile.close();
		// Convert stringstream to string
		fileString = shaderStream.str();
	}
	catch (ifstream::failure e) {
		cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ\n";
	}
	// Put the shader code in heap by copying it there
	shaderCode = fileString.c_str();
	toRet = new char[fileString.length() + 1];
	strncpy_s(toRet, fileString.length() + 1, shaderCode, fileString.length() + 1);
	return toRet;
}

// Rewrite and retool if working with geometry shader
unsigned int compileShader(bool isVertShader, const char * shaderCode) {
	unsigned int shaderID;
	int success;
	char infoLog[CHARBUFSIZ];

	shaderID = (isVertShader) ? glCreateShader(GL_VERTEX_SHADER) : glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(shaderID, 1, &shaderCode, NULL);
	glCompileShader(shaderID);
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shaderID, CHARBUFSIZ, NULL, infoLog);
		if (isVertShader)
			cerr << "ERROR::SHADER::VERTEX::COMPILATIONS_FAILED\n" << infoLog << endl;
		else
			cerr << "ERROR::SHADER::FRAGMENT::COMPILATIONS_FAILED\n" << infoLog << endl;
	}
	return shaderID;
}

Shader::Shader(const GLchar* vertPath, const GLchar* fragPath) {
	unsigned int vertID, fragID;
	int success;
	char infoLog[CHARBUFSIZ];
	const char * vertShaderCode;
	const char * fragShaderCode;

	// Read shader files
	vertShaderCode = readShaderFile(vertPath);
	fragShaderCode = readShaderFile(fragPath);
	// Compile shader files
	vertID = compileShader(true, vertShaderCode);
	fragID = compileShader(false, fragShaderCode);
	// Create shader program
	ID = glCreateProgram();
	glAttachShader(ID, vertID);
	glAttachShader(ID, fragID);
	glLinkProgram(ID);
	// Print linking errors if any 
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, CHARBUFSIZ, NULL, infoLog);
		cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
	}
	// Detach and delete shader
	glDetachShader(ID, vertID);
	glDetachShader(ID, fragID);
	glDeleteShader(vertID);
	glDeleteShader(fragID);
	delete[] vertShaderCode;
	delete[] fragShaderCode;
}

Shader::~Shader() {
	glDeleteProgram(ID);
}

void Shader::use() {
	glUseProgram(ID);
}

void Shader::setBool(const string &name, bool val) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)val);
}
void Shader::setInt(const string &name, int val) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), val);
}
void Shader::setFloat(const string &name, float val) const {
	glUniform1f(glGetUniformLocation(ID, name.c_str()), val);
}
void Shader::setMat3(const string &name, const mat3 &val) const {
	glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, false, &val[0][0]);
}
void Shader::setMat4(const string &name, const mat4 &val) const {
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, false, &val[0][0]);
}
void Shader::setVec3(const string &name, const vec3 &val) const {
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &val[0]);
}
void Shader::setVec4(const string &name, const vec4 &val) const {
	glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &val[0]);
}
