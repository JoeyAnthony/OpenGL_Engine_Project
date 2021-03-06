#pragma once
#include <vector>
#include "Vertex.h"
#include "Texture.h"
#include "Shader.h"

struct Bounds {
	glm::vec3 maxBounds = glm::vec3(0, 0, 0);
	glm::vec3 minBounds = glm::vec3(0, 0, 0);

	Bounds operator+ (glm::vec3 rh)
	{
		return {maxBounds+rh, minBounds+rh};
	}

	Bounds operator* (glm::vec3 rh)
	{
		return { maxBounds * rh, minBounds * rh };
	}
};
class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	void Draw(Shader* shader);
	/*
	*Returns bounds of THIS mesh
	*/
	Bounds getBounds();

	void freeData();

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, Bounds bounds);
	Mesh();
	~Mesh();

private:
	GLuint VAO, VBO, EBO;
	Bounds bounds;
	
	void setupMesh();
};

