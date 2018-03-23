#include "ControllerComponent.h"
#include "Tools.h"



void ControllerComponent::Update()
{
	const float speed = 20;
	if (Keyboard::GetKeyboard()['a']) Move(0, Tools::DeltaTime()*speed);
	if (Keyboard::GetKeyboard()['d']) Move(180, Tools::DeltaTime()*speed);
	if (Keyboard::GetKeyboard()['w']) Move(90, Tools::DeltaTime()*speed);
	if (Keyboard::GetKeyboard()['s']) Move(270, Tools::DeltaTime()*speed);

	if (Keyboard::GetKeyboard()['q']) CameraZ(-speed * Tools::DeltaTime());
	if (Keyboard::GetKeyboard()['z']) CameraZ(speed * Tools::DeltaTime());

	glm::vec2 mouse = Mouse::GetMousePos();
	Mouse(mouse.x, mouse.y);

	//std::cout << "Update camera" << std::endl;
}

void ControllerComponent::CameraZ(float fac)
{
	parent->Position.y += fac;
}

void ControllerComponent::Move(float angle, float fac)
{
	parent->Position.x += (float)cos((parent->Rotation.y + angle) / 180.0f * M_PI) * fac;
	parent->Position.z += (float)sin((parent->Rotation.y + angle) / 180.0f * M_PI) * fac;
	
	//std::cout << "Move" << std::endl;
}

bool justMoved = false;

void ControllerComponent::Mouse(int x, int y)
{

}

void ControllerComponent::init(uint32_t id)
{
	Component::init(id);
}

ControllerComponent::ControllerComponent()
{
}


ControllerComponent::~ControllerComponent()
{
}
