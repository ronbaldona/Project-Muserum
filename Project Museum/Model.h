#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"

struct Materials {
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec4 emission;
	float shininess;
};

class Model
{
	vector<Mesh> meshes;
	vector<Texture> textures_loaded;
	string directory;
	Materials material;

	void loadModel(string path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
public:
	mat4 model;	// Transformation mat

	Model();
	~Model();

	Model(const char* path) { 
		model = mat4(1.0f);
		loadModel(path);
	}
	void setMaterials(vec4 ambient, vec4 diffuse, vec4 specular, vec4 emission, float shininess);
	void sendMaterialInfo(Shader shader) const;
	void translate(const float &tx, const float &ty, const float &tz);
	void translate(const vec3 &tvec);
	void scale(const float &sx, const float &sy, const float &sz);
	void scale(const vec3 &svec);
	void rotate(const float degrees, const float ax, const float ay, const float az);
	void rotate(const float degrees, const vec3 & axis);
	void Draw(Shader shader);
};

