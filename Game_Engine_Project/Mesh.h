#pragma once
#include <vector>
#include "Vertex.h"
#include "Texture.h"
#include "Shader.h"

class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	void Draw(Shader shader);

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	Mesh();
	~Mesh();

private:
	GLuint VAO, VBO, EBO;
	
	void setupMesh();
};

