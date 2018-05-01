#include "GameSetup.h"

#include "CameraComponent.h"
#include "ModelComponent.h"
#include "RenderComponent.h"
#include "ControllerComponent.h"
#include "TestRotation.h"
#include "CollisionComponent.h"

GameObject* GameSetup::AddGameObject(GameObject obj)
{
	uint32_t hash = NewGameObjectNum();
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
	GameObject* camera = GameObject::Create(this);
	
	CameraComponent* cc = new CameraComponent(true);
	camera->AddComponent(cc);


	ModelComponent* floorPanel = new ModelComponent("Assets/Levels/ArenaModels/FloorPanel", "FloorPanel.obj", true);
	floorPanel->model.shader = Shader("Assets/Shaders/PBR.vs", "Assets/Shaders/PBR.fs");

	ModelComponent* largePanel = new ModelComponent("Assets/Levels/ArenaModels/LargePanel", "LargePanel.obj", true);
	largePanel->model.shader = Shader("Assets/Shaders/PBR.vs", "Assets/Shaders/PBR.fs");

	ModelComponent* jumpPlatform = new ModelComponent("Assets/Levels/ArenaModels/JumpPlatform", "JumpPlatform.obj", true);
	jumpPlatform->model.shader = Shader("Assets/Shaders/PBR.vs", "Assets/Shaders/PBR.fs");

	glm::vec3 scale = glm::vec3(6, 6, 6);
	int horizontal = 4;
	int vertical = 6;
	glm::vec3 floorDistance = (floorPanel->model.getBounds().maxBounds + glm::abs(floorPanel->model.getBounds().minBounds)) * scale;

	for (int i = 0; i <= horizontal; i++)
	{

		for (int j = 0; j <= vertical; j++)
		{
			if (i == 0 || i == horizontal || j == 0 || j == vertical)
			{
				GameObject* copyFloor = GameObject::Create(this);
				copyFloor->AddComponent(new ModelComponent(floorPanel));
				copyFloor->AddComponent(new RenderComponent());
				copyFloor->AddComponent(new CollisionComponent);
				copyFloor->transform.scale = scale;
				copyFloor->transform.position = glm::vec3(floorDistance.x * (i - horizontal/2),
														0, 
														floorDistance.z * (j - vertical / 2) );
			}
		}

	}

	GameObject* largeP = GameObject::Create(this);
	largeP->AddComponent(largePanel);
	largeP->AddComponent(new RenderComponent());
	largeP->AddComponent(new CollisionComponent);
	largeP->transform.scale = scale;
	largeP->transform.position = glm::vec3(0, 16, 0);
	largeP->transform.rotation = glm::vec3(0, 90, 0);

	glm::vec3 jumpplatDistance = (largePanel->model.getBounds().maxBounds + jumpPlatform->model.getBounds().maxBounds) * scale;

	GameObject* jumpPlat1 = GameObject::Create(this);
	jumpPlat1->AddComponent(jumpPlatform);
	jumpPlat1->AddComponent(new RenderComponent());
	jumpPlat1->AddComponent(new CollisionComponent);
	jumpPlat1->transform.scale = scale;
	jumpPlat1->transform.position = glm::vec3(jumpplatDistance.x, largeP->transform.position.y / 2, jumpplatDistance.z/1.5);

	GameObject* jumpPlat2 = GameObject::Create(this);
	jumpPlat2->AddComponent(jumpPlatform);
	jumpPlat2->AddComponent(new RenderComponent());
	jumpPlat2->AddComponent(new CollisionComponent);
	jumpPlat2->transform.scale = scale;
	jumpPlat2->transform.position = glm::vec3(jumpplatDistance.x, largeP->transform.position.y / 2, jumpplatDistance.z / -1.5);

	GameObject* jumpPlat3 = GameObject::Create(this);
	jumpPlat3->AddComponent(jumpPlatform);
	jumpPlat3->AddComponent(new RenderComponent());
	jumpPlat3->AddComponent(new CollisionComponent);
	jumpPlat3->transform.scale = scale;
	jumpPlat3->transform.position = glm::vec3(-jumpplatDistance.x, largeP->transform.position.y / 2, jumpplatDistance.z / 1.5);

	GameObject* jumpPlat4 = GameObject::Create(this);
	jumpPlat4->AddComponent(jumpPlatform);
	jumpPlat4->AddComponent(new RenderComponent());
	jumpPlat4->AddComponent(new CollisionComponent);
	jumpPlat4->transform.scale = scale;
	jumpPlat4->transform.position = glm::vec3(-jumpplatDistance.x, largeP->transform.position.y / 2, jumpplatDistance.z / -1.5);

	GameObject* jumpPlatCenter = GameObject::Create(this);
	jumpPlatCenter->AddComponent(jumpPlatform);
	jumpPlatCenter->AddComponent(new RenderComponent());
	jumpPlatCenter->AddComponent(new CollisionComponent);
	jumpPlatCenter->transform.scale = scale;
	


	////railgun
	//GameObject* railgun = GameObject::Create(this);
	//ModelComponent* gunmodel = new ModelComponent("Assets/Models/railgun", "railgun.obj");
	//railgun->AddComponent(gunmodel);
	//RenderComponent* gunr = new RenderComponent();
	//railgun->AddComponent(gunr);
	//TestRotation* rotc2 = new TestRotation();
	//railgun->AddComponent(rotc2);
	//railgun->transform.position = glm::vec3(3, 0, 0);
	//railgun->transform.scale = glm::vec3(0.2, 0.2, 0.2);
	//gunmodel->model.shader = Shader("Assets/Shaders/PBR.vs", "Assets/Shaders/PBR.fs");
	//railgun->AddComponent(new CollisionComponent);

	//GameObject* plane = GameObject::Create(this);
	//ModelComponent* planemodel = new ModelComponent("Assets/Models/Plane", "Plane.obj", true);
	//planemodel->model.shader = Shader("Assets/Shaders/PBR.vs", "Assets/Shaders/PBR.fs");
	//plane->AddComponent(planemodel);
	//plane->AddComponent(new RenderComponent());
	//plane->transform.scale = glm::vec3(.5, .5, .5);

	//int count = 8;
	//int spacing = 2;
	//int x = 0;
	//int y = 0;
	//for (int i = 0; i < count; i++)
	//{
	//	y = 0;
	//	for (int j = 0; j < count; j++)
	//	{

	//		GameObject* block = GameObject::Create(this);
	//		ModelComponent* mc = new ModelComponent("Assets/Models/Sphere", "Sphere.obj");
	//		block->AddComponent(mc);

	//		RenderComponent* rc = new RenderComponent();
	//		block->AddComponent(rc);

	//		block->transform.position = glm::vec3(x - count / 2 - spacing, y - count / 2 - spacing,-5);
	//		mc->model.shader = Shader("Assets/Shaders/PBR_NoTex.vs", "Assets/Shaders/PBR_NoTex.fs");

	//		mc->model.shader.UseShader();
	//		mc->model.shader.SetVec3("unidiffuse", glm::vec3(1, 0, 0));
	//		mc->model.shader.SetFLoat("unimetallic", glm::max((1.0f/count) * j, 0.1f));
	//		//mc->model.shader.SetFLoat("uniao", glm::max((1.0f / count) * j, 0.1f));
	//		mc->model.shader.SetFLoat("uniroughness", glm::max((1.0f / count) * i, 0.1f));

	//		glUseProgram(0);

	//		y += spacing;
	//	}
	//	x += spacing;
	//}



}

GameSetup::GameSetup(Window* window)
{
	this->window = window;
}


GameSetup::~GameSetup()
{
}
