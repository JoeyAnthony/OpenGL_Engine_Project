#pragma once
#include <string>
#include <vector>
#include <filesystem>

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include "Mesh.h"
#include "Shader.h"
#include "GameObject.h"

class Model
{
public:
	//data
	Shader shader;

	//functions
	/*
	* Initialize
	*/
	void initModel();

	/*
	* Draws the model with a shader(in render call)
	*/
	void Draw(Shader shader);

	/*
	* Add texture to a mesh manually
	*/
	void AddTexManual(std::string texname, std::string typeName, unsigned int meshindex);

	/*
	* Returns bounds of ALL meshes
	* Or get them with the transform position added
	*/
	Bounds getBounds();
	Model();
	Model(const Model* model);
	Model(std::string directory, std::string modelname, GameObject* parent, bool searchMat = false);
	~Model();

private:
	//data
	GameObject* parent;
	std::string directory;
	std::vector<Mesh> meshes;
	std::vector<Texture> loadedTextures;
	Bounds modelBounds;
	bool searchMaterials = false;

	//functions
	/*
	* calculates bounds of ALL meshes
	*/
	void calcModelBounds();

	void loadModel(std::string directory, std::string modelname);

	void freeData();

	//Assimp
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> searchTexturesInDir();
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};

