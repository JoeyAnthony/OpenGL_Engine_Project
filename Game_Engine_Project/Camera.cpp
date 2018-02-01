#include "Camera.h"
#include "Input.h"
#include "Tools.h"
#include <iostream>

glm::vec2 lastmousepos;
float pitch = 0;
float yaw = 0;

void Camera::update()
{
	right = glm::cross(forward, up);

	if (Keyboard::GetKey(GLFW_KEY_W))
		position += (glm::normalize(forward) * speed) * Tools::DeltaTime();

	if (Keyboard::GetKey(GLFW_KEY_S))
		position -= (glm::normalize(forward) * speed) * Tools::DeltaTime();

	if (Keyboard::GetKey(GLFW_KEY_D))
		position += (glm::normalize(right) * speed) * Tools::DeltaTime();

	if (Keyboard::GetKey(GLFW_KEY_A))
		position -= (glm::normalize(right) * speed) * Tools::DeltaTime();


	if (Keyboard::GetKey(GLFW_KEY_Q))
		position += (glm::normalize(up) * speed) * Tools::DeltaTime();

	if (Keyboard::GetKey(GLFW_KEY_Z))
		position -= (glm::normalize(up) * speed) * Tools::DeltaTime();


	pitch += (lastmousepos.y - Mouse::GetMousePos().y) * sensitivity;
	yaw += (Mouse::GetMousePos().x - lastmousepos.x) * sensitivity;

	//std::cout << "rot: " << pitch << " " <<yaw << std::endl;
	//std::cout << "offset: " << mouseoffset.x << " " << mouseoffset.y  << std::endl;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	//calculate forward vector
	glm::vec3 front;
	front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	front.y = sin(glm::radians(pitch));
	front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	forward = glm::normalize(front);

	lastmousepos = Mouse::GetMousePos();
}

Camera::Camera()
{
	lastmousepos = Mouse::GetMousePos();
}


Camera::~Camera()
{
}
