#pragma once
#include "GameObject.h"
#include "Vertex.h"
#include "CameraComponent.h"
#include "RenderComponent.h"
#include "Shader.h"

class LineRenderer
{
public:
	Transform transform;
	std::vector<glm::vec3> vertices;
	glm::vec3 color = glm::vec3(0, 1, 0);

	void Draw(CameraComponent* cam);
	void DrawLine();
	LineRenderer(Bounds bounds);
	LineRenderer();
	~LineRenderer();

private:
	GLuint VBO, VAO;
	Shader shader;

	void createBuffers(glm::vec3 * array);
};

