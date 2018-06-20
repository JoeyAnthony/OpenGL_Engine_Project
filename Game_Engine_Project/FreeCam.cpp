#include "FreeCam.h"
#include "Input.h"
#include "GameSetup.h"
#include "GameObject.h"



void FreeCam::init(uint32_t id)
{
}

void FreeCam::Update()
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


	//mouse input

	//lastmouseposition = Mouse::GetMousePos();

	Window* win = parent->GetSetup()->window;
	glm::vec2 moved = Mouse::GetMousePos() - glm::vec2(win->Width() / 2.0, win->Height() / 2.0);
	//parent->transform.rotation.x += (lastmouseposition.y - Mouse::GetMousePos().y) * sensitivity;
	//parent->transform.rotation.y += (Mouse::GetMousePos().x - lastmouseposition.x) * sensitivity;

	parent->transform.rotation.x += -moved.y * sensitivity;
	parent->transform.rotation.y += moved.x * sensitivity;


	//mouseMoved = false;
	glfwSetCursorPos(win->GetWindow(), win->Width() / 2.0, win->Height() / 2.0);

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
}

FreeCam::FreeCam()
{
	lastmouseposition = Mouse::GetMousePos();
}


FreeCam::~FreeCam()
{
}
