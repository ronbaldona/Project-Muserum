/* Special Thanks to learnopengl.com for the assimp code!
 * Base class for rendering 3D objects
 * Default lighting model is based on Phong shading
 */
#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"

const float PI = 3.14159265359f;

// Materials for Phong Illumination
struct Materials {
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec4 emission;
	float shininess;
};

class Model
{
private:
	vector<Mesh> meshes;
	vector<Texture> textures_loaded;
	string directory;
	Materials material;
	// Change later?
	float xMin, yMin, zMin;
	float xMax, yMax, zMax;

	// Loading the model
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);

protected:
	void loadModel(string path);
	inline void initTransformMat() {
		rotMat = mat4(1.0f);
		scaleMat = mat4(1.0f);
		transMat = mat4(1.0f);
	}
	virtual void setUniformMaterial(Shader shader) const;

public:
	mat4 transMat, rotMat, scaleMat;

	Model();
	~Model();

	Model(const char* path);

	// Transformation methods
	void translate(const float &tx, const float &ty, const float &tz);
	void translate(const vec3 &tvec);
	void scale(const float &sx, const float &sy, const float &sz);
	void scale(const vec3 &svec);
	void rotate(const float degrees, const float ax, const float ay, const float az);	// Takes degrees, not radians
	void rotate(const float degrees, const vec3 & axis);
	void rotateAboutOrigin(const float degrees);	// TODO

	inline void printRotationMat() {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				cout << rotMat[i][j] << ", ";
			}
			cout << endl;
		}
	}

	// Gets angle (in radians) and axis of rotaiton from vector v1 to v2
	static void getAxisAngle(float& angle, vec3& axis, vec3 v1, vec3 v2);

	// Render the object
	void setMaterialVal(const vec4 ambient, const vec4 diffuse, const vec4 specular, const vec4 emission, 
								const float shininess);
	virtual void Draw(Shader shader, const mat4& view, const mat4& projection);
};

