#include "Model.h"
#include <filesystem>
#include "Tools.h"
namespace fs = std::experimental::filesystem;

void Model::initModel()
{
}

Model::Model()
{
}

Model::Model(const Model * model)
{
	shader = model->shader;
	directory = model->directory;
	meshes = model->meshes;
	loadedTextures = model->loadedTextures;
	modelBounds = model->modelBounds;
	searchMaterials = model->searchMaterials;
}

Model::Model(std::string directory, std::string modelname, GameObject* parent, bool searchMat)
{
	searchMaterials = searchMat;
	loadModel(directory, modelname);
	this->parent = parent;
	initModel();
}


Model::~Model()
{

}

void Model::Draw(Shader* shader)
{
	for (unsigned int i = 0; i < meshes.size(); i++)
	{
		meshes[i].Draw(shader);
	}
}

void Model::AddTexManual(std::string texname, std::string typeName, unsigned int meshindex)
{
	std::string path = directory + "/" + texname;
	Texture tex(path);
	tex.type = typeName;

	loadedTextures.push_back(tex);
	meshes[meshindex].textures.push_back(tex);
}

void Model::calcModelBounds()
{
	for (int i = 0; i < meshes.size(); i++)
	{
		//calculate modelbounds
		modelBounds.maxBounds.x = glm::max(modelBounds.maxBounds.x, meshes[i].getBounds().maxBounds.x);
		modelBounds.maxBounds.y = glm::max(modelBounds.maxBounds.y, meshes[i].getBounds().maxBounds.y);
		modelBounds.maxBounds.z = glm::max(modelBounds.maxBounds.z, meshes[i].getBounds().maxBounds.z);

		modelBounds.minBounds.x = glm::min(modelBounds.minBounds.x, meshes[i].getBounds().minBounds.x);
		modelBounds.minBounds.y = glm::min(modelBounds.minBounds.y, meshes[i].getBounds().minBounds.y);
		modelBounds.minBounds.z = glm::min(modelBounds.minBounds.z, meshes[i].getBounds().minBounds.z);
	}
}

Bounds Model::getBounds()
{
	return modelBounds;
}

void Model::loadModel(std::string directory, std::string modelname)
{
	std::string path = directory +"/"+ modelname;
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		Debug("ERROR::ASSIMP::" << importer.GetErrorString() << std::endl);
		return;
	}
	this->directory = directory;

	processNode(scene->mRootNode, scene);

}

void Model::freeData()
{
	for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i].freeData();
	}

	for (int i = 0; i < loadedTextures.size(); i++)
	{
		loadedTextures[i].freeData();
	}
}

void Model::processNode(aiNode * node, const aiScene * scene)
{
	//node contains indices to get meshes from a scene
	//a mesh will then be processed
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh *assimpMesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(assimpMesh, scene));
	}


	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}

	calcModelBounds();
}

Mesh Model::processMesh(aiMesh * mesh, const aiScene * scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	Bounds meshBounds;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vert;
		
		vert.position = glm::vec3(
			mesh->mVertices[i].x,
			mesh->mVertices[i].y,
			mesh->mVertices[i].z);

		vert.normal = glm::vec3(
			mesh->mNormals[i].x,
			mesh->mNormals[i].y,
			mesh->mNormals[i].z);

		//calculate mesh bounds
		meshBounds.maxBounds.x = glm::max(meshBounds.maxBounds.x, vert.position.x);
		meshBounds.maxBounds.y = glm::max(meshBounds.maxBounds.y, vert.position.y);
		meshBounds.maxBounds.z = glm::max(meshBounds.maxBounds.z, vert.position.z);

		meshBounds.minBounds.x = glm::min(meshBounds.minBounds.x, vert.position.x);
		meshBounds.minBounds.y = glm::min(meshBounds.minBounds.y, vert.position.y);
		meshBounds.minBounds.z = glm::min(meshBounds.minBounds.z, vert.position.z);

		if (mesh->mTextureCoords[0])
		{
			vert.texcoord = glm::vec2(
				mesh->mTextureCoords[0][i].x,
				mesh->mTextureCoords[0][i].y);
		}

		if (mesh->HasTangentsAndBitangents())
		{
			vert.tangent = glm::vec3(
				mesh->mTangents[i].x,
				mesh->mTangents[i].y,
				mesh->mTangents[i].z);
		}

		vertices.push_back(vert);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	if (searchMaterials)
	{
		std::vector<Texture> allMaps = searchTexturesInDir();
		if (allMaps.size() == 0)
			Debug("No textures found in directory" << std::endl);
		textures.insert(textures.end(), allMaps.begin(), allMaps.end());
	}
	else if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.begin(), specularMaps.begin(), specularMaps.end());

		std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
		textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
		
		std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
		textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
	}

	return Mesh(vertices, indices, textures, meshBounds);
}

std::vector<Texture> Model::searchTexturesInDir()
{
	std::vector<Texture> textures;
	for (fs::path it : fs::directory_iterator(directory))
	{
		std::string path = it.string();
		bool skip = false;
		//skip if texture is already loaded
		for (int j = 0; j < loadedTextures.size(); j++)
		{

			if (std::strcmp(loadedTextures[j].filepath.c_str(), path.c_str()) == 0)
			{
				textures.push_back(loadedTextures[j]);
				skip = true;
				break;
			}
		}

		if (skip)
			continue;

		//check texturetype
		std::string typeName;
		std::string filename = it.filename().string();
		if (filename.find("diffuse") != std::string::npos)
		{
			typeName = "texture_diffuse";
		}
		else if (filename.find("albedo") != std::string::npos)
		{
			typeName = "texture_diffuse";
		}
		else if (filename.find("ambientocclusion") != std::string::npos)
		{
			typeName = "texture_ambientocclusion";
		}
		else if (filename.find("AO") != std::string::npos)
		{
			typeName = "texture_ambientocclusion";
		}
		else if (filename.find("metallic") != std::string::npos)
		{
			typeName = "texture_metallic";
		}
		else if (filename.find("normal") != std::string::npos)
		{
			typeName = "texture_normal";
		}
		else if (filename.find("roughness") != std::string::npos)
		{
			typeName = "texture_roughness";
		}

		//load texture
		Texture texture(path);
		texture.type = typeName;
		textures.push_back(texture);
		loadedTextures.push_back(texture);
	}

	return textures;
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial * mat, aiTextureType type, std::string typeName)
{
	std::vector<Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		bool skip = false;

		aiString str;
		mat->GetTexture(type, i, &str);

		
		//check if texture is already loaded
		for (int j = 0; j < loadedTextures.size(); j++)
		{
			if (std::strcmp(loadedTextures[j].filepath.c_str(), str.C_Str()) == 0)
			{
				textures.push_back(loadedTextures[j]);
				skip = true;
				break;
			}
		}

		if (skip)
			continue;

		std::string path = directory + "/" + str.C_Str();
			
		Texture texture(path);
		texture.type = typeName;
		textures.push_back(texture);
		loadedTextures.push_back(texture);
	}



	return textures;
}
