#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "variables.h"
#include "Mesh.h"
class Model
{
	vector<Mesh> meshes;
	vector<Texture> textures_loaded;
	string directory;

	void loadModel(string path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
public:
	Model();
	~Model();

	Model(const char* path) { loadModel(path); }
	void Draw(Shader shader);
};

