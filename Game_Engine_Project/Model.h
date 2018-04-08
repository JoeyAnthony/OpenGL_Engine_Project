#pragma once
#include <string>
#include <vector>
#include <filesystem>

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include "Mesh.h"
#include "Shader.h"

class Model
{
public:
	//data
	Shader shader;
	//functions
	void initModel();
	void Draw(Shader shader);
	void AddTexManual(std::string texname, std::string typeName, unsigned int meshindex);
	Model();
	Model(std::string directory, std::string modelname, bool searchMat = false);
	~Model();

private:
	//data
	std::string directory;
	std::vector<Mesh> meshes;
	std::vector<Texture> loadedTextures;
	bool searchMaterials = false;
	//functions
	void loadModel(std::string directory, std::string modelname);
	//Assimp
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> searchTexturesInDir();
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};

