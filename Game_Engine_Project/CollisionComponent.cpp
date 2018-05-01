#include "CollisionComponent.h"
#include "GameObject.h"
#include "GameSetup.h"

void CollisionComponent::Render(CameraComponent * cam)
{
	lines.Draw(cam);
}

void CollisionComponent::init(uint32_t id)
{
	lines = LineRenderer(parent->GetComponent<ModelComponent>()->model.getBounds());
	Component::init(id);
	parent->GetSetup()->AddDrawable(this);
}

void CollisionComponent::Update()
{
	lines.transform = parent->transform;

}

CollisionComponent::CollisionComponent()
{
}


CollisionComponent::~CollisionComponent()
{
}
