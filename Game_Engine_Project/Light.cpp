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
	if (glm::length((parent->transform.position - lastpos)) > 0.001)
	{
		needUpdate = true;
		parent->GetSetup()->GetObjectContainer()->lights[lightID].pos = parent->transform.position; 
	}
	if (needUpdate)
	{
		needUpdate = false;
	}
	lastpos = parent->transform.position;
}

void Light::freeData()
{
	parent->GetSetup()->RemoveLight(lightID);
}

Light::Light() : Light(vec3(23.47, 21.31, 20.79))
{
}



Light::Light(glm::vec3 color)
{
	initcolor = color;
}


Light::~Light()
{
}
