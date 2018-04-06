#pragma once
#include "GameObject.h"
#include "Component.h"
#include "Input.h"

class CameraComponent : public Component
{
public:
	float speed = 5.0f;
	float sensitivity = 0.3f;

	void init(uint32_t id) override;
	void Update() override;
	void LateUpdate() override;
	void Render();

	glm::mat4 view;
	glm::mat4 projection;

	CameraComponent();
	~CameraComponent();
};

