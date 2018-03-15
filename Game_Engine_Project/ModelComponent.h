#pragma once
#include "glad\glad.h"

#include <string>
#include <vector>
#include <list>
#include <unordered_map>

#include "Component.h"
#include "Texture.h"
#include "Shader.h"
#include "Vertex.h"
#include "Model.h"

class ModelComponent : public Component
{
public:
	Model model;

	std::string modelpath;
	std::string texturepath;
	bool hasmodel = false;

	Shader transformshader;

	int texcount = 0;
	std::vector<Texture> textures;
	std::vector<Vertex> vertices;
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	void init(uint32_t id) override;
	void addShader(std::string vs, std::string fs);
	void addTexture(std::string uniformName, std::string path);
	void bindTextures();

public:

	ModelComponent(std::string directory, std::string modelname);
	ModelComponent();
	~ModelComponent(void);
};