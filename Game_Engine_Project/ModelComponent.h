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

class ModelComponent : public Component
{
public:

	std::string modelpath;
	std::string texturepath;
	bool hasmodel = false;

	Shader transformshader;

	std::vector<Texture> textures;
	std::vector<Vertex> vertices;
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	void init(uint32_t id) override;
	void addTexture(std::string uniformName, std::string path);
	void bindTextures();

public:

	ModelComponent();
	~ModelComponent(void);
};