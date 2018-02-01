#pragma once
#include "GameObject.h"
#include "Component.h"
#include "Input.h"

#define _USE_MATH_DEFINES
#include <math.h>

class ControllerComponent : public Component
{
public:

	void Update() override;
	void Move(float angle, float speed);
	void CameraZ(float fac);
	void Mouse(int x, int y);

	void init(uint32_t id) override;

	ControllerComponent();
	~ControllerComponent();
};

