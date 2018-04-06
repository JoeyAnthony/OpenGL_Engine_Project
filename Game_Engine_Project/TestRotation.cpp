#include "TestRotation.h"



void TestRotation::Update()
{
	parent->transform.rotation += glm::vec3(0, 10, 0) * Tools::DeltaTime();
	parent->transform.position = glm::vec3(0, 0, 0);

}

TestRotation::TestRotation()
{
}


TestRotation::~TestRotation()
{
}
