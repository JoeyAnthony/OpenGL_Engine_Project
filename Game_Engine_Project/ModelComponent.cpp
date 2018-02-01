#include "ModelComponent.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>


/**
* Replaces a substring in a string
*/
static std::string replace(std::string str, const std::string &toReplace, const std::string &replacement)
{
	size_t index = 0;
	while (true)
	{
		index = str.find(toReplace, index);
		if (index == std::string::npos)
			break;
		str.replace(index, toReplace.length(), replacement);
		++index;
	}
	return str;
}


/**
* Splits a string into substrings, based on a seperator
*/
static std::vector<std::string> split(std::string str, const std::string &seperator)
{
	std::vector<std::string> ret;
	size_t index;
	while (true)
	{
		index = str.find(seperator);
		if (index == std::string::npos)
			break;
		ret.push_back(str.substr(0, index));
		str = str.substr(index + 1);
	}
	ret.push_back(str);
	return ret;
}

/**
* Turns a string to lowercase
*/
static inline std::string toLower(std::string data)
{
	std::transform(data.begin(), data.end(), data.begin(), ::tolower);
	return data;
}


/**
* Cleans up a line for processing
*/
static inline std::string cleanLine(std::string line)
{
	line = replace(line, "\t", " ");
	while (line.find("  ") != std::string::npos)
		line = replace(line, "  ", " ");
	if (line == "")
		return "";
	if (line[0] == ' ')
		line = line.substr(1);
	if (line == "")
		return "";
	if (line[line.length() - 1] == ' ')
		line = line.substr(0, line.length() - 1);
	return line;
}


/**
* Loads an object model
*/
void ModelComponent::LoadModel(const std::string & fileName)
{
	if (hasmodel)
		return;

	std::cout << "Loading " << fileName << std::endl;
	std::string dirName = fileName;
	if (dirName.rfind("/") != std::string::npos)
		dirName = dirName.substr(0, dirName.rfind("/"));
	if (dirName.rfind("\\") != std::string::npos)
		dirName = dirName.substr(0, dirName.rfind("\\"));
	if (fileName == dirName)
		dirName = "";


	std::ifstream pFile(fileName.c_str());

	if (!pFile.is_open())
	{
		std::cout << "Could not open file " << fileName << std::endl;
		return;
	}


	ObjGroup* currentGroup = new ObjGroup();
	currentGroup->materialIndex = -1;


	while (!pFile.eof())
	{
		std::string line;
		std::getline(pFile, line);
		line = cleanLine(line);
		if (line == "" || line[0] == '#') //skip empty or commented line
			continue;

		std::vector<std::string> params = split(line, " ");
		params[0] = toLower(params[0]);

		if (params[0] == "v")
			vertices.push_back(Vec3f((float)atof(params[1].c_str()), (float)atof(params[2].c_str()), (float)atof(params[3].c_str())));
		else if (params[0] == "vn")
			normals.push_back(Vec3f((float)atof(params[1].c_str()), (float)atof(params[2].c_str()), (float)atof(params[3].c_str())));
		else if (params[0] == "vt")
			texcoords.push_back(Vec2f((float)atof(params[1].c_str()), (float)atof(params[2].c_str())));
		else if (params[0] == "f")
		{
			for (size_t ii = 4; ii <= params.size(); ii++)
			{
				Face face;

				for (size_t i = ii - 3; i < ii; i++)	//magische forlus om van quads triangles te maken ;)
				{
					Vertex vertex;
					std::vector<std::string> indices = split(params[i == (ii - 3) ? 1 : i], "/");
					if (indices.size() >= 1)	//er is een positie
						vertex.position = atoi(indices[0].c_str()) - 1;
					if (indices.size() == 2)		//alleen texture
						vertex.texcoord = atoi(indices[1].c_str()) - 1;
					if (indices.size() == 3)		//v/t/n of v//n
					{
						if (indices[1] != "")
							vertex.texcoord = atoi(indices[1].c_str()) - 1;
						vertex.normal = atoi(indices[2].c_str()) - 1;
					}
					face.vertices.push_back(vertex);
				}
				currentGroup->faces.push_back(face);
			}
		}
		else if (params[0] == "s")
		{//smoothing groups
		}
		else if (params[0] == "mtllib")
		{
			loadMaterialFile(dirName + "/" + params[1], dirName);
		}
		else if (params[0] == "usemtl")
		{
			if (currentGroup->faces.size() != 0)
				groups.push_back(currentGroup);
			currentGroup = new ObjGroup();
			currentGroup->materialIndex = -1;

			for (size_t i = 0; i < materials.size(); i++)
			{
				MaterialInfo* info = materials[i];
				if (info->name == params[1])
				{
					currentGroup->materialIndex = i;
					break;
				}
			}
			if (currentGroup->materialIndex == -1)
				std::cout << "Could not find material name " << params[1] << std::endl;
		}
	}
	groups.push_back(currentGroup);

	hasmodel = true;
	makeindexlist();
}

void ModelComponent::loadMaterialFile(const std::string &fileName, const std::string &dirName)
{
	std::cout << "Loading " << fileName << std::endl;
	std::ifstream pFile(fileName.c_str());
	if (!pFile.is_open())
	{
		std::cout << "Could not open file " << fileName << std::endl;
		return;
	}

	MaterialInfo* currentMaterial = NULL;

	while (!pFile.eof())
	{
		std::string line;
		std::getline(pFile, line);
		line = cleanLine(line);
		if (line == "" || line[0] == '#')
			continue;

		std::vector<std::string> params = split(line, " ");
		params[0] = toLower(params[0]);

		if (params[0] == "newmtl")
		{
			if (currentMaterial != NULL)
			{
				materials.push_back(currentMaterial);
			}
			currentMaterial = new MaterialInfo();
			currentMaterial->name = params[1];
		}
		else if (params[0] == "map_kd")
		{
			std::string tex = params[1];
			if (tex.find("/"))
				tex = tex.substr(tex.rfind("/") + 1);
			if (tex.find("\\"))
				tex = tex.substr(tex.rfind("\\") + 1);
			//TODO
			currentMaterial->texture = new Texture(dirName + "/" + tex + "/");
		}
		else if (params[0] == "kd")
		{//TODO, diffuse color
		}
		else if (params[0] == "ka")
		{//TODO, ambient color
		}
		else if (params[0] == "ks")
		{//TODO, specular color
		}
		else if (
			params[0] == "illum" ||
			params[0] == "map_bump" ||
			params[0] == "map_ke" ||
			params[0] == "map_ka" ||
			params[0] == "map_d" ||
			params[0] == "d" ||
			params[0] == "ke" ||
			params[0] == "ns" ||
			params[0] == "ni" ||
			params[0] == "td" ||
			params[0] == "tf" ||
			params[0] == "tr" ||
			false)
		{
			//these values are usually not used for rendering at this time, so ignore them
		}
		else
			std::cout << "Didn't parse " << params[0] << " in material file" << std::endl;
	}
	if (currentMaterial != NULL)
		materials.push_back(currentMaterial);

}

void ModelComponent::init(uint32_t id)
{
	Component::init(id);

	static const float cubeVertices[] = {
		-1.0, -1.0,  1.0,	0.0f, 1.0f, 0.0f,	0.0f, 0.0f,		// bottom left back		0
		1.0, -1.0,  1.0,	1.0f, 0.0f, 0.0f,	1.0f, 0.0f,		// bottom right back	1
		-1.0,  1.0,  1.0,	1.0f, 1.0f, 0.0f,	0.0f, 1.0f,		//top left back			2
		1.0,  1.0,  1.0,	0.0f, 0.0f, 1.0f,	1.0f, 1.0f,		// top right back		3

		-1.0, -1.0, -1.0,	0.0f, 1.0f, 0.0f,	0.0f, 0.0f,		// bottom left front	4
		1.0, -1.0, -1.0,	1.0f, 0.0f, 0.0f,	1.0f, 0.0f,		// bottom right front	5
		-1.0,  1.0, -1.0,	1.0f, 1.0f, 0.0f,	0.0f, 1.0f,		//top left front		6
		1.0,  1.0, -1.0,	0.0f, 0.0f, 1.0f,	1.0f, 1.0f		// top right front		7
	};

	static const unsigned int cubeIndices[] = {
		//front
		4, 5, 7,
		7, 6, 4,
		//rightside
		5, 1, 3,
		3, 7, 5,
		//back
		1, 0, 2,
		2, 3, 1,
		//left
		0, 4, 6,
		6, 2, 0,
		//bottom
		4, 5, 1,
		1, 0, 4,
		//top
		6, 7, 3,
		3, 2, 6
	};

	transformshader = Shader("SimpleVertexShader.glsl", "SimpleFragmentShader.glsl");
	//texture = Texture("Assets/Textures/Sanic2.png");
	texture = Texture("Assets/Textures/thomas420.jpg");

	//create vbo and vao
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);

	//bind vao
	glBindVertexArray(VAO);

	//bind vbo buffer and store vertex data in it
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

	//bind and buffer vbo array, the vao will hold it too
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

	//set vertex attributes for shaders
	/*
	(location = 0) vertex position location is 0 like in the shader
	Since the previously defined VBO was bound before calling glVertexAttribPointer,
	vertex attribute 0 is now associated with its vertex data
	*/
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	//Enabling the attribute because they are disabled by default
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//textures
	glActiveTexture(GL_TEXTURE0);
	texture.Bind();
	//glActiveTexture(GL_TEXTURE1);
	//texture2.Bind();


	transformshader.UseShader(); //bind shader
	transformshader.SetInt("texture1", 0);
	//transformshader.SetInt("texture2", 1);

	shaderlocations.modelmatrixloc = glGetUniformLocation(transformshader.shaderid_, "model");
	shaderlocations.viewmatrixloc = glGetUniformLocation(transformshader.shaderid_, "view");
	shaderlocations.projectionmatrixloc = glGetUniformLocation(transformshader.shaderid_, "projection");
	
	glUseProgram(0); //unbind shader
}

void ModelComponent::makeindexlist()
{
	for (ObjGroup* group: groups)
	{
		for (Face& face : group->faces)
		{
			for (Vertex& vertex : face.vertices)
			{

			}
		}
	}
}

MaterialInfo::MaterialInfo()
{
	texture = NULL;
}

ModelComponent::ModelComponent()
{

}

ModelComponent::ModelComponent(const std::string & filename, const std::string & texfile)
{
	modelpath = filename;
	texturepath = texfile;
	LoadModel(filename);
	texture.LoadTexture(texfile);
}

ModelComponent::~ModelComponent(void)
{
	//glDeleteBuffers();
}






