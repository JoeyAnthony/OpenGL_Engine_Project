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

	//void init(uint32_t id) override;
	void Update() override;
	void LateUpdate() override;

	ProjectileCannon(float interval, bool autom, ModelComponent* model);
	~ProjectileCannon();
};

