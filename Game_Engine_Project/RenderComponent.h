#pragma once
#include <glad\glad.h>

#include "Component.h"
#include "GameObject.h"
#include "ModelComponent.h"
#include "CameraComponent.h"


class RenderComponent : public Component
{
private:

public:
	ModelComponent* modelinfo;
	bool hasmodelinfo = false;
	glm::mat4 model;

	virtual void Render(CameraComponent* camera);
	void init(uint32_t id) override;
	void freeData() override;

	RenderComponent();
	~RenderComponent();
};

