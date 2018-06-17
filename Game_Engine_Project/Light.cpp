#include "Light.h"
#include "GameSetup.h"

using namespace glm;

void Light::setColor(glm::vec3 color)
{
	parent->GetSetup()->GetObjectContainer()->lights[lightID].color = color;
}

void Light::init(uint32_t id)
{
	lightID = parent->GetSetup()->AddLight(parent->transform.position, initcolor);
}

void Light::Update()
{
	if (glm::length((parent->transform.position - lastpos)) > 0.1)
	{
		needUpdate = true;
		parent->GetSetup()->GetObjectContainer()->lights[lightID].pos = parent->transform.position; //bug light gets added
	}
	if (needUpdate)
	{
		parent->GetSetup()->UpdateShaders();
		needUpdate = false;
	}
	lastpos = parent->transform.position;
}

void Light::freeData()
{
	parent->GetSetup()->RemoveLight(lightID);
}

Light::Light() : Light(vec3(20.47, 5.31, 5.79))
{
}



Light::Light(glm::vec3 color)
{
	initcolor = color;
}


Light::~Light()
{
}
