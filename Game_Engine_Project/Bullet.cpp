#include "Bullet.h"
#include "GameObject.h"
#include "Tools.h"



void Bullet::outOfBounds()
{
}

void Bullet::Update()
{
	parent->transform.position += direction * travelSpeed * Tools::DeltaTime();
	float l = glm::length(parent->transform.position);
	if (glm::length(parent->transform.position) > 30.0f)
	{
		parent->Destroy();
	}
}

void Bullet::LateUpdate()
{
}


Bullet::Bullet(float travelSpeed, glm::vec3 direction)
{
	this->travelSpeed = travelSpeed;
	this->direction = direction;
}

Bullet::~Bullet()
{
}
