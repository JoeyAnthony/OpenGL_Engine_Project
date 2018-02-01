#include "Component.h"
#include "GameObject.h"



const uint32_t Component::GetID()
{
	return ID;
}

const bool Component::IsInitialized()
{
	return Initialized;
}

void Component::Update()
{
}

void Component::LateUpdate()
{
	//std::cout << "Should not happen" << std::endl;
}

void Component::FixedUpdate()
{
}

void Component::init(uint32_t id)
{
	if (Initialized)
	{
		std::cout << "Already initialized" << std::endl;
		return;
	}
	std::cout << "Component init" << std::endl;
	ID = id;
	Initialized = true;
}

Component::Component()
{
}

