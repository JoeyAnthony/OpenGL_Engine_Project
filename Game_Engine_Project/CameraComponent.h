#pragma once
#include "GameObject.h"
#include "Component.h"
#include "Vec.h"
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
	glm::mat4 projection = glm::perspective(45.0f, (1280.0f / 720.0f), 0.1f, 100.0f);

	CameraComponent();
	~CameraComponent();
};

