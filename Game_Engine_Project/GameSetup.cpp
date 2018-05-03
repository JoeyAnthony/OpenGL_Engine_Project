#include "GameSetup.h"

#include "CameraComponent.h"
#include "ModelComponent.h"
#include "RenderComponent.h"
#include "ControllerComponent.h"
#include "TestRotation.h"
#include "CollisionComponent.h"
#include "FreeCam.h"
#include "GameCam.h"


GameObject* GameSetup::AddGameObject(GameObject obj)
{
	uint32_t hash = NewGameObjectNum();
	obj.ID = hash;
	objectContainer.MasterGameObjectList.insert({ hash, obj });
	objectContainer.MasterGameObjectList[hash].init(hash);
	return &objectContainer.MasterGameObjectList[hash];
}

void GameSetup::AddDrawable(RenderComponent * component)
{
	if (!component->IsInitialized())
	{
		std::cout << "ERROR: Component NOT Initialized:" << typeid(component).name() << std::endl;
		return;
	}
	objectContainer.drawables.insert(std::pair<uint32_t, RenderComponent*>(component->GetID(), component));
}

void GameSetup::AddDrawable(CameraComponent * component)
{
	if (!component->IsInitialized())
	{
		std::cout << "Component not Initialized:" << typeid(component).name() << std::endl;
		return;
	}
	objectContainer.cameras.insert(std::pair<uint32_t, CameraComponent*>(component->GetID(), component));
}

//void GameSetup::AddDrawable(CollisionComponent * component)
//{
//	if (!component->IsInitialized())
//	{
//		std::cout << "Component not Initialized:" << typeid(component).name() << std::endl;
//		return;
//	}
//	objectContainer.cameras.insert(std::pair<uint32_t, CollisionComponent*>(component->GetID(), component));
//}

int GameSetup::NewGameObjectNum()
{
	return ++GameObjectCount;
}

void GameSetup::UpdateScene()
{
	for (auto it : objectContainer.MasterGameObjectList)
	{
		it.second.Update();
	}
}

void GameSetup::LateUpdateScene()
{
	for (auto it : objectContainer.MasterGameObjectList)
	{
		//it.second.LateUpdate();
	}
}

void GameSetup::FixedUpdateScene()
{
	for (auto it : objectContainer.MasterGameObjectList)
	{
		//it.second.FixedUpdate();
	}
}

ObjectContainer * GameSetup::GetObjectContainer()
{
	return &objectContainer;
}

void GameSetup::Render()
{
	for (auto cam : objectContainer.cameras)
	{
		cam.second->Render();

		for (auto draw : objectContainer.drawables)
		{
			draw.second->Render(cam.second);
		}
	}
}

void GameSetup::CreateScene()
{
	ModelComponent* floormodel = new ModelComponent("Assets/Levels/TopViewShooter/Enviroment/floor", "Floor_Plane.obj", true);
	floormodel->model.shader = Shader("Assets/Shaders/PBR.vs", "Assets/Shaders/PBR.fs");

	ModelComponent* playermodel = new ModelComponent("Assets/Levels/TopViewShooter/Characters/player", "Player.obj", true);
	playermodel->model.shader = Shader("Assets/Shaders/PBR.vs", "Assets/Shaders/PBR.fs");




	GameObject* camera = GameObject::Create(this);
	camera->name = "mainCam";
	
	CameraComponent* cc = new CameraComponent(true);
	camera->AddComponent(cc);
	camera->AddComponent(new FreeCam());

	//CollisionComponent* col = new CollisionComponent();
	//col->isStatic = false;
	//camera->AddComponent(col);

	float height = 0.4455;
	
	GameObject* floor = GameObject::Create(this);
	floor->AddComponent(floormodel);
	floor->AddComponent(new RenderComponent());
	floor->transform.position = glm::vec3();

	GameObject* player = GameObject::Create(this);
	player->AddComponent(playermodel);
	player->AddComponent(new RenderComponent());
	player->transform.scale = glm::vec3(0.2, 0.2, 0.2);
	player->transform.position = glm::vec3(0, height, 0);

	
	

	GameObject* plane = GameObject::Create(this);
	ModelComponent* planemodel = new ModelComponent("Assets/Models/Plane", "Plane.obj", true);
	planemodel->model.shader = Shader("Assets/Shaders/PBR.vs", "Assets/Shaders/PBR.fs");
	plane->AddComponent(planemodel);
	plane->AddComponent(new RenderComponent());
	plane->transform.scale = glm::vec3(.5, .5, .5);
	plane->transform.position = glm::vec3(0, -3, 0);



}

GameSetup::GameSetup(Window* window)
{
	this->window = window;
}


GameSetup::~GameSetup()
{
}
