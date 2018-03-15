#pragma once
#include <glm\glm.hpp>
#include <assimp\vector2.h>
#include <assimp\vector3.h>
class Vertex
{
public:
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texcoord;
	glm::vec3 tangent;
	glm::vec4 color;

	Vertex(const glm::vec3 &position, const glm::vec4 &color, const glm::vec2 &texcoord, const glm::vec3&normal) : position(position), color(color), texcoord(texcoord), normal(normal) {}
	Vertex(const glm::vec3 &position, const glm::vec3&normal, const glm::vec2 &texcoord) : position(position), normal(normal), texcoord(texcoord) {}
	//Vertex(const aiVector3D & position, const aiVector3D & normal, const aiVector3D & texcoord)
	//{
	//	this->position = glm::vec3(position.x, position.y, position.z);
	//	this->normal = glm::vec3(normal.x, normal.y, normal.z);
	//	this->texcoord = glm::vec2(texcoord.x, texcoord.y);
	//}

	Vertex();
	~Vertex();
};

