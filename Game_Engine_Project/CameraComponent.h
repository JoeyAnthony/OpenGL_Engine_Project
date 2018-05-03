#pragma once
#include "GameObject.h"
#include "Component.h"

class CameraComponent : public Component
{
public:
	bool ismaincam = false;

	void init(uint32_t id) override;
	void Update() override;
	void LateUpdate() override;
	void Render();

	glm::mat4 view;
	glm::mat4 projection;

	CameraComponent(bool ismaincam = false);
	~CameraComponent();
};

