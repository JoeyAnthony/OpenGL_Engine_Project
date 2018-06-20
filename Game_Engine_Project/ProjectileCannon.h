#pragma once
#include "Component.h"
#include "ModelComponent.h"

class ProjectileCannon : public Component
{
public:
	bool canShoot = true;
	float travelSpeed = 20.0f;
	bool automatic = true;
	float shootInterval = 1.0f;
	float intervalCounter = 0;
	ModelComponent* modelcmp;
	glm::vec3 lightColor = {20, 20, 20};

	//void init(uint32_t id) override;
	void Update() override;

	ProjectileCannon(float interval, bool autom, ModelComponent* model);
	ProjectileCannon(float interval, float travelspeed, bool autom, ModelComponent* model, glm::vec3 lightcolor);
	~ProjectileCannon();
};

