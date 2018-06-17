#include "ProjectileCannon.h"
#include "Tools.h"
#include "Input.h"
#include "GameObject.h"
#include "Bullet.h"
#include "RenderComponent.h"
#include "CollisionComponent.h"
#include "Light.h"

void ProjectileCannon::Update()
{
	if (!automatic)
	{
		canShoot = false;
		if (Mouse::GetButton(GLFW_MOUSE_BUTTON_1))
		{
			canShoot = true;
		}
	}

	if (intervalCounter > shootInterval && canShoot)
	{
		//shoot
		GameObject* gm = GameObject::Create(parent->GetSetup());
		gm->AddComponent(modelcmp);
		gm->AddComponent(new RenderComponent());
		gm->AddComponent(new CollisionComponent());
		gm->AddComponent(new Bullet(travelSpeed, parent->transform.forward));
		gm->AddComponent(new Light());
		gm->transform.position = parent->transform.position;
		gm->transform.rotation = parent->transform.rotation;
		gm->transform.scale = glm::vec3(0.3, 0.3, 0.3);

		intervalCounter = 0;
	}
	else if(!canShoot)
	{
		intervalCounter = shootInterval + 1;
	}
	intervalCounter += Tools::DeltaTime();
}

void ProjectileCannon::LateUpdate()
{
}

ProjectileCannon::ProjectileCannon(float interval, bool autom, ModelComponent* model)
{
	shootInterval = interval;
	automatic = autom;
	modelcmp = model;
}

ProjectileCannon::~ProjectileCannon()
{
}
