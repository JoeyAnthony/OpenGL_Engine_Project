#include "PlayerInput.h"
#include "GameSetup.h"
#include "GameObject.h"
#include "Input.h"
#include "Tools.h"
#include <glm\gtx\intersect.hpp>
#include <glm\gtc\quaternion.hpp>



void PlayerInput::init(uint32_t id)
{
}

void PlayerInput::Update()
{
	glm::vec3 movevec = {0, 0, 0};
	if (Keyboard::GetKey(GLFW_KEY_W))
		movevec += glm::vec3(0, 0, -1);

	if (Keyboard::GetKey(GLFW_KEY_A))
		movevec += glm::vec3(-1, 0, 0);

	if (Keyboard::GetKey(GLFW_KEY_S))
		movevec += glm::vec3(0, 0, 1);

	if (Keyboard::GetKey(GLFW_KEY_D))
		movevec += glm::vec3(1, 0, 0);

	if(!glm::length(movevec) == 0)
		movevec = glm::normalize(movevec);
	
	parent->transform.position += movevec *speed * Tools::DeltaTime();
	//field bound checks
	parent->transform.position = glm::max(parent->transform.position, -12.5f);
	parent->transform.position = glm::min(parent->transform.position, 12.5f);

	glm::vec2 mousepos = Mouse::GetMousePos();
	float x = (2.0f * mousepos.x) / (float)parent->GetSetup()->window->Width() - 1.0f;
	float y = 1.0f - (2.0f * mousepos.y) / (float)parent->GetSetup()->window->Height();

	float rot =  std::atan2<GLfloat>(y, x) + glm::pi<float>() /2;
	

	parent->transform.rotation.y = glm::degrees(rot);

	parent->UpdateTransform();
}

PlayerInput::PlayerInput(CameraComponent* maincam)
{
	this->maincam = maincam;
}


PlayerInput::~PlayerInput()
{
}
