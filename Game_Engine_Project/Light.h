#pragma once
#include "Component.h"

class Light : public Component
{
private:
	uint32_t lightID;
public:
	glm::vec3 initcolor;
	glm::vec3 lastpos;
	bool needUpdate = true;
	void setColor(glm::vec3 color);

	void init(uint32_t id) override;
	void Update() override;
	void LateUpdate() override {};
	void freeData() override;

	Light();
	Light(glm::vec3 color);
	~Light();
};

