#pragma once
#include "Component.h"
#include "CameraComponent.h"

class PlayerInput : public Component
{
private:
	float speed = 5.0f;
	CameraComponent* maincam;

public:

	void init(uint32_t id) override;
	void Update() override;

	PlayerInput(CameraComponent* maincam);
	~PlayerInput();
};

