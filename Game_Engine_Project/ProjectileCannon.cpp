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
		gm->transform.position = parent->transform.position + glm::vec3(0, 0.2f, 0) + parent->transform.forward;
		gm->transform.rotation = parent->transform.rotation;
		gm->transform.scale = glm::vec3(0.3, 0.3, 0.3);
		gm->AddComponent(modelcmp);
		gm->AddComponent(new RenderComponent());
		CollisionComponent* cc = new CollisionComponent(bulletLineRenderer);
		cc->excludeID = parent->ID;
		gm->AddComponent(cc);
		gm->AddComponent(new Bullet(travelSpeed, parent->transform.forward));
		gm->AddComponent(new Light(lightColor));

		intervalCounter = 0;
	}
	else if(!canShoot)
	{
		intervalCounter = shootInterval + 1;
	}
	intervalCounter += Tools::DeltaTime();
}

void ProjectileCannon::freeData()
{
	bulletLineRenderer->free_data();
}

ProjectileCannon::ProjectileCannon(float interval, bool autom, ModelComponent* model)
{
	shootInterval = interval;
	automatic = autom;
	modelcmp = model;
	bulletLineRenderer = new LineRenderer(model->model.getBounds());
}

ProjectileCannon::ProjectileCannon(float interval, float travelspeed, bool autom, ModelComponent * model, glm::vec3 lightcolor) : ProjectileCannon(interval, autom, model)
{
	travelSpeed = travelspeed;
	lightColor = lightcolor;
	bulletLineRenderer = new LineRenderer(model->model.getBounds());
}

ProjectileCannon::~ProjectileCannon()
{
}
