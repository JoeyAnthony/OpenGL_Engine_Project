#pragma once
#include "Component.h"

class Bullet : public Component
{
public:
	float travelSpeed = 0;
	glm::vec3 direction;

	//void init(uint32_t id) override;
	void outOfBounds();
	void Update() override;
	void LateUpdate() override;

	Bullet(float travelSpeed, glm::vec3 direction);
	~Bullet();
};

