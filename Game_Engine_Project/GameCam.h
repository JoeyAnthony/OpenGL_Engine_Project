#pragma once
#include "Component.h"

class GameCam : public Component
{
private:
	float camHeight = 7.0f;
	float camPlayerZOffset = 4;
	float followSpeed = 4.0f;
	glm::vec3 campos;
	glm::vec3 lookdir;

	GameObject* player;
	
	void CalcTransform();

public:

	void init(uint32_t id) override;
	void Update() override;
	void LateUpdate() override;


	GameCam(GameObject* player);
	~GameCam();
};

