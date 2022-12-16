#pragma once
#include <iostream>
#include<vector>
#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <unordered_map>
#include <../SpeeDEngine/Drawable.h>


class Model:public Drawable
{
public:
	Model(const char* path);
	void Draw(Shader& shader) override;
	
private:
	std::unordered_map<std::string, Texture_> LoadedTexture;
	std::vector<Mesh> meshes;
	std::string directory;
	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture_> loadMaterialTextures(aiMaterial* mat,aiTextureType type, std::string typeName);
};