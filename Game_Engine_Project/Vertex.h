#pragma once
#include <glm\glm.hpp>
class Vertex
{
public:
	//Vertex();
	glm::vec3 position;
	glm::vec4 color;
	glm::vec2 texcoord;
	glm::vec3 normal;

	Vertex(const glm::vec3 &position, const glm::vec4 &color, const glm::vec2 &texcoord) : position(position), color(color), texcoord(texcoord) {}
	~Vertex();
};

