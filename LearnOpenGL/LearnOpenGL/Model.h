#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include"Mesh.h"
#include"TextureLoader.h"

class Model {
public:
	Model(char* path = NULL);
	void Draw(Shader shader);

	
private:
	vector<Texture> texturesLoaded;
	vector<Mesh>meshes;
	string directory;

	void loadModel(string path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	vector<Texture> loadMaterialTextures(aiMaterial *mat,
		aiTextureType type, string typeName);
};