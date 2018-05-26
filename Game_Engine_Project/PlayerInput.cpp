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
	if (Keyboard::GetKey(GLFW_KEY_W))
		parent->transform.position += glm::vec3(0, 0, -1) * speed * Tools::DeltaTime();

	if (Keyboard::GetKey(GLFW_KEY_A))
		parent->transform.position += glm::vec3(-1, 0, 0) * speed * Tools::DeltaTime();

	if (Keyboard::GetKey(GLFW_KEY_S))
		parent->transform.position += glm::vec3(0, 0, 1) * speed * Tools::DeltaTime();

	if (Keyboard::GetKey(GLFW_KEY_D))
		parent->transform.position += glm::vec3(1, 0, 0) * speed * Tools::DeltaTime();

	
	glm::vec2 mousepos = Mouse::GetMousePos();
	float x = (2.0f * mousepos.x) / (float)parent->GetSetup()->window->Width() - 1.0f;
	float y = 1.0f - (2.0f * mousepos.y) / (float)parent->GetSetup()->window->Height();

	float rot =  std::atan2<GLfloat>(y, x) + glm::pi<float>() /2;
	

	parent->transform.rotation.y = glm::degrees(rot);

	parent->UpdateTransform();
}

void PlayerInput::LateUpdate()
{
}

PlayerInput::PlayerInput(CameraComponent* maincam)
{
	this->maincam = maincam;
}


PlayerInput::~PlayerInput()
{
}
