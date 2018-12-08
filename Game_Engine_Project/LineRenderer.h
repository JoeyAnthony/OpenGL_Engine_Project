#pragma once
#include "GameObject.h"
#include "Vertex.h"
#include "CameraComponent.h"
#include "RenderComponent.h"
#include "Shader.h"

class CollisionComponent;

class LineRenderer
{
public:
	Transform transform;
	std::vector<glm::vec3> vertices;
	glm::vec3 color = glm::vec3(0, 1, 0);

	void Draw(CameraComponent* cam);
	void DrawLine();
	void free_data();

	LineRenderer(Bounds bounds);
	LineRenderer(const LineRenderer& lr);
	LineRenderer();
	~LineRenderer();

private:
	GLuint VBO, VAO;

	void createBuffers(glm::vec3 * array);
};

