#pragma once
#include "RenderComponent.h"
#include "Model.h"
#include "LineRenderer.h"
#include "CameraComponent.h"

class Shader;

class CollisionComponent : public RenderComponent
{
public:
	static Shader* lineshader;
	
	struct HitPlane
	{
		bool hit = false;
		float distance = 0;
		glm::vec3 normal;
	};

	LineRenderer* lines;
	bool isStatic = true;
	ModelComponent* modelcmp;
	Bounds bounds;
	Transform lastTransform;
	uint32_t excludeID = 0;

	void Render(CameraComponent* cam);
	void init(uint32_t id) override;
	void Update() override;
	float smallestOverlap(float posaxis, float negaxis);
	glm::vec3 largestInVec(glm::vec3 vec);
	bool checkCollision(glm::vec3& push);
	void checkCollision();
	bool collide(Bounds obounds, Bounds mbounds);
	void freeData() override;
	
	CollisionComponent();
	explicit CollisionComponent(LineRenderer* lr);
	~CollisionComponent();
};

