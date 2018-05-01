#pragma once
#include "RenderComponent.h"
#include "Model.h"
#include "LineRenderer.h"
#include "CameraComponent.h"

class CollisionComponent : public RenderComponent
{
public:
	LineRenderer lines;

	void Render(CameraComponent* cam);
	void init(uint32_t id) override;
	void Update() override;
	Bounds bounds;


	CollisionComponent();
	~CollisionComponent();
};

