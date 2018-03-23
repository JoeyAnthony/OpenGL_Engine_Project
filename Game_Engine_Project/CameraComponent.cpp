#include "CameraComponent.h"
#include "GameSetup.h"

glm::vec2 lastmouseposition;

void CameraComponent::init(uint32_t id)
{
	Component::init(id);
	parent->GetSetup()->AddDrawable(this);
	std::cout << "Camerainit" << std::endl;
}

void CameraComponent::Update()
{
	parent->transform.right = glm::cross(parent->transform.forward, parent->transform.up);

	if (Keyboard::GetKey(GLFW_KEY_W))
		parent->transform.position += (glm::normalize(parent->transform.forward) * speed) * Tools::DeltaTime();

	if (Keyboard::GetKey(GLFW_KEY_S))
		parent->transform.position -= (glm::normalize(parent->transform.forward) * speed) * Tools::DeltaTime();

	if (Keyboard::GetKey(GLFW_KEY_D))
		parent->transform.position += (glm::normalize(parent->transform.right) * speed) * Tools::DeltaTime();

	if (Keyboard::GetKey(GLFW_KEY_A))
		parent->transform.position -= (glm::normalize(parent->transform.right) * speed) * Tools::DeltaTime();


	if (Keyboard::GetKey(GLFW_KEY_Q))
		parent->transform.position += (glm::normalize(parent->transform.up) * speed) * Tools::DeltaTime();

	if (Keyboard::GetKey(GLFW_KEY_Z))
		parent->transform.position -= (glm::normalize(parent->transform.up) * speed) * Tools::DeltaTime();


	parent->transform.rotation.x += (lastmouseposition.y - Mouse::GetMousePos().y) * sensitivity;
	parent->transform.rotation.y += (Mouse::GetMousePos().x - lastmouseposition.x) * sensitivity;

	//std::cout << "rot: " << pitch << " " <<yaw << std::endl;
	//std::cout << "offset: " << mouseoffset.x << " " << mouseoffset.y  << std::endl;

	if (parent->transform.rotation.x > 89.0f)
		parent->transform.rotation.x = 89.0f;
	if (parent->transform.rotation.x < -89.0f)
		parent->transform.rotation.x = -89.0f;

	//calculate forward vector
	glm::vec3 front;
	front.x = cos(glm::radians(parent->transform.rotation.x)) * cos(glm::radians(parent->transform.rotation.y));
	front.y = sin(glm::radians(parent->transform.rotation.x));
	front.z = cos(glm::radians(parent->transform.rotation.x)) * sin(glm::radians(parent->transform.rotation.y));
	parent->transform.forward = glm::normalize(front);

	lastmouseposition = Mouse::GetMousePos();

	Window* win = parent->GetSetup()->window;

	//glfwSetCursorPos(win->GetWindow(), win->Width()/2.0, win->Height()/2.0);

	//std::cout << parent->transform.rotation.x << " " << parent->transform.rotation.y << " " << parent->transform.rotation.z << std::endl;
}

void CameraComponent::LateUpdate() 
{

}

void CameraComponent::Render()
{
	view = glm::lookAt(parent->transform.position, parent->transform.position + parent->transform.forward, glm::vec3(0, 1, 0));
}

CameraComponent::CameraComponent()
{
	lastmouseposition = Mouse::GetMousePos();
}

CameraComponent::~CameraComponent()
{
}
