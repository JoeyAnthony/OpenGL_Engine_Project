#pragma once
#include "Component.h"


class FreeCam : public Component
{
private:
	float speed = 5.0f;
	glm::vec2 lastmouseposition;
	bool mouseMoved = false;
	float sensitivity = 0.25f;

public:
	

	void init(uint32_t id) override;
	void Update() override;

	FreeCam();
	~FreeCam();
};

