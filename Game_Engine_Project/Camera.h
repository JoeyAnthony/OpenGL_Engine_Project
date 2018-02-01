#pragma once
#include <glm\glm.hpp>

class Camera
{
public:
	glm::vec3 position = glm::vec3(0, 0, 0);
	glm::vec3 forward = glm::vec3(0, 0, 0);
	glm::vec3 right = glm::vec3(0, 0, 0);
	glm::vec3 up = glm::vec3(0, 1, 0);
	//glm::mat4 view;

	float speed = 5.0f;
	float sensitivity = 0.3f;

	void update();


	Camera();
	~Camera();
};

