#include "Bullet.h"
#include "GameObject.h"
#include "Tools.h"

void Bullet::init(uint32_t id)
{
	parent->transform.forward = direction;
}

void Bullet::outOfBounds()
{
}

void Bullet::Update()
{
	if (direction == glm::vec3())
		parent->transform.position += glm::vec3(0, 0, 1) *travelSpeed * Tools::DeltaTime();
	else
		parent->transform.position += parent->transform.forward * travelSpeed * Tools::DeltaTime();

	float l = glm::length(parent->transform.position);
	if (glm::length(parent->transform.position) > 30.0f)
	{
		parent->Destroy();
	}

	parent->UpdateTransform();
}


Bullet::Bullet(float travelSpeed, glm::vec3 direction): travelSpeed(travelSpeed), direction(direction)
{
	
}

Bullet::~Bullet()
{
}
