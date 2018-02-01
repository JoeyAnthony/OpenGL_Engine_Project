#pragma once
#include "glad\glad.h"

#include <string>
#include <vector>
#include <list>
#include <unordered_map>

#include "Component.h"
#include "Vec.h"
#include "Texture.h"
#include "Shader.h"



class Vertex
{
public:
	int position;
	int normal;
	int texcoord;
};

class Face
{
public:
	std::list<Vertex> vertices;
};

class MaterialInfo
{
public:
	MaterialInfo();
	std::string name;
	Texture* texture;
};

class ObjGroup
{
public:
	std::string name;
	int materialIndex;
	std::list<Face> faces;
};

struct VertexData
{
	Vec3f position;
	Vec2f texcoord;
	Vec3f normal;
};
class ModelComponent : public Component
{
public:
	struct ShaderLocationData
	{
		GLuint modelmatrixloc;
		GLuint viewmatrixloc;
		GLuint projectionmatrixloc;
	};

	std::string modelpath;
	std::string texturepath;
	bool hasmodel = false;

	std::vector<Vec3f>	vertices;
	std::vector<Vec3f>	normals;
	std::vector<Vec2f>	texcoords;
	std::vector<ObjGroup*> groups;
	std::vector<MaterialInfo*> materials;

	ShaderLocationData shaderlocations;
	Shader transformshader;

	GLuint VBO;
	GLuint VAO;
	GLuint EBO;

	Texture texture;

	void LoadModel(const std::string &fileName);
	void loadMaterialFile(const std::string &fileName, const std::string &dirName = "");
	void init(uint32_t id) override;
	void makeindexlist();
	void addtexture(); //add textures dynamically

public:

	ModelComponent();
	ModelComponent(const std::string &filename, const std::string &texfile = "");
	~ModelComponent(void);
};