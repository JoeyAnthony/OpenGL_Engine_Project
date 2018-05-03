#include "CameraComponent.h"
#include "GameSetup.h"



void CameraComponent::init(uint32_t id)
{
	Component::init(id);
	parent->GetSetup()->AddDrawable(this);
	if (ismaincam)
		parent->GetSetup()->mainCamID = GetID();
	std::cout << "Camerainit" << std::endl;

	projection = glm::perspective(45.0f, ((GLfloat)parent->GetSetup()->window->Width() / (GLfloat)parent->GetSetup()->window->Height()), 0.1f, 1000.0f);
}

void CameraComponent::Update()
{

}

void CameraComponent::LateUpdate() 
{

}

void CameraComponent::Render()
{
	view = glm::lookAt(parent->transform.position, parent->transform.position + parent->transform.forward, glm::vec3(0, 1, 0));
}

CameraComponent::CameraComponent(bool ismaincam)
{
	this->ismaincam = ismaincam;
}

CameraComponent::~CameraComponent()
{
}
