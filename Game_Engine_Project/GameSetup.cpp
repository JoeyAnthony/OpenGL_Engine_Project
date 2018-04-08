#include "GameSetup.h"

#include "CameraComponent.h"
#include "ModelComponent.h"
#include "RenderComponent.h"
#include "ControllerComponent.h"
#include "TestRotation.h"

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
		std::cout << "Component not Initialized:" << typeid(component).name() << std::endl;
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
	
	CameraComponent* cc = new CameraComponent();
	camera->AddComponent(cc);

	////Level
	////floor
	//glm::vec3 scale = glm::vec3(3, 3, 3);
	//GameObject* floor1 = GameObject::Create(this);
	//ModelComponent* pm1 = new ModelComponent("Assets/Levels/Arena/Floor", "sci-fi-floor1.obj", true);
	//pm1->model.shader = Shader("Assets/Shaders/PBR.vs", "Assets/Shaders/PBR.fs");
	//floor1->AddComponent(pm1);
	//floor1->AddComponent(new RenderComponent());
	//floor1->transform.scale = scale;

	//GameObject* floor2 = GameObject::Create(this);
	//ModelComponent* pm2 = new ModelComponent("Assets/Levels/Arena/Floor", "sci-fi-floor2.obj", true);
	//pm2->model.shader = Shader("Assets/Shaders/PBR.vs", "Assets/Shaders/PBR.fs");
	//floor2->AddComponent(pm2);
	//floor2->AddComponent(new RenderComponent());
	//floor2->transform.scale = scale;

	//GameObject* floor3 = GameObject::Create(this);
	//ModelComponent* pm3 = new ModelComponent("Assets/Levels/Arena/Floor", "sci-fi-floor3.obj", true);
	//pm3->model.shader = Shader("Assets/Shaders/PBR.vs", "Assets/Shaders/PBR.fs");
	//floor3->AddComponent(pm3);
	//floor3->AddComponent(new RenderComponent());
	//floor3->transform.scale = scale;

	//GameObject* floor4 = GameObject::Create(this);
	//ModelComponent* pm4 = new ModelComponent("Assets/Levels/Arena/Floor", "sci-fi-floor4.obj", true);
	//pm4->model.shader = Shader("Assets/Shaders/PBR.vs", "Assets/Shaders/PBR.fs");
	//floor4->AddComponent(pm4);
	//floor4->AddComponent(new RenderComponent());
	//floor4->transform.scale = scale;

	////highfloor
	//GameObject* highfloor = GameObject::Create(this);
	//ModelComponent* model5 = new ModelComponent("Assets/Levels/Arena/HighFloor", "cementfloor.obj", true);
	//model5->model.shader = Shader("Assets/Shaders/PBR.vs", "Assets/Shaders/PBR.fs");
	//highfloor->AddComponent(model5);
	//highfloor->AddComponent(new RenderComponent());
	//highfloor->transform.scale = scale;

	////platforms
	//GameObject* platform1 = GameObject::Create(this);
	//ModelComponent* model6 = new ModelComponent("Assets/Levels/Arena/Platform", "sci-fi-platform1.obj", true);
	//model6->model.shader = Shader("Assets/Shaders/PBR.vs", "Assets/Shaders/PBR.fs");
	//platform1->AddComponent(model6);
	//platform1->AddComponent(new RenderComponent());
	//platform1->transform.scale = scale;

	//GameObject* platform2 = GameObject::Create(this);
	//ModelComponent* model7 = new ModelComponent("Assets/Levels/Arena/Platform", "sci-fi-platform2.obj", true);
	//model7->model.shader = Shader("Assets/Shaders/PBR.vs", "Assets/Shaders/PBR.fs");
	//platform2->AddComponent(model7);
	//platform2->AddComponent(new RenderComponent());
	//platform2->transform.scale = scale;

	//GameObject* platform3 = GameObject::Create(this);
	//ModelComponent* model8 = new ModelComponent("Assets/Levels/Arena/Platform", "sci-fi-platform3.obj", true);
	//model8->model.shader = Shader("Assets/Shaders/PBR.vs", "Assets/Shaders/PBR.fs");
	//platform3->AddComponent(model8);
	//platform3->AddComponent(new RenderComponent());
	//platform3->transform.scale = scale;

	//GameObject* platform4 = GameObject::Create(this);
	//ModelComponent* model9 = new ModelComponent("Assets/Levels/Arena/Platform", "sci-fi-platform4.obj", true);
	//model9->model.shader = Shader("Assets/Shaders/PBR.vs", "Assets/Shaders/PBR.fs");
	//platform4->AddComponent(model9);
	//platform4->AddComponent(new RenderComponent());
	//platform4->transform.scale = scale;

	////walls
	//GameObject* wall1 = GameObject::Create(this);
	//ModelComponent* model10 = new ModelComponent("Assets/Levels/Arena/Wall", "sci-fi-wall1.obj", true);
	//model10->model.shader = Shader("Assets/Shaders/PBR.vs", "Assets/Shaders/PBR.fs");
	//wall1->AddComponent(model10);
	//wall1->AddComponent(new RenderComponent());
	//wall1->transform.scale = scale;

	//GameObject* wall2 = GameObject::Create(this);
	//ModelComponent* model11 = new ModelComponent("Assets/Levels/Arena/Wall", "sci-fi-wall2.obj", true);
	//model11->model.shader = Shader("Assets/Shaders/PBR.vs", "Assets/Shaders/PBR.fs");
	//wall2->AddComponent(model11);
	//wall2->AddComponent(new RenderComponent());
	//wall2->transform.scale = scale;

	//GameObject* wall3 = GameObject::Create(this);
	//ModelComponent* model12 = new ModelComponent("Assets/Levels/Arena/Wall", "sci-fi-wall3.obj", true);
	//model12->model.shader = Shader("Assets/Shaders/PBR.vs", "Assets/Shaders/PBR.fs");
	//wall3->AddComponent(model12);
	//wall3->AddComponent(new RenderComponent());
	//wall3->transform.scale = scale;

	//GameObject* wall4 = GameObject::Create(this);
	//ModelComponent* model13 = new ModelComponent("Assets/Levels/Arena/Wall", "sci-fi-wall4.obj", true);
	//model13->model.shader = Shader("Assets/Shaders/PBR.vs", "Assets/Shaders/PBR.fs");
	//wall4->AddComponent(model13);
	//wall4->AddComponent(new RenderComponent());
	//wall4->transform.scale = scale;

	////robot
	//GameObject* robot = GameObject::Create(this);
	//ModelComponent* mc = new ModelComponent("Assets/Models/Robot", "model.dae", true);
	//robot->AddComponent(mc);
	//RenderComponent* rc = new RenderComponent();
	//robot->AddComponent(rc);
	//TestRotation* rotc = new TestRotation();
	//robot->AddComponent(rotc);
	//robot->transform.position = glm::vec3(0, 0, 0);
	//mc->model.shader = Shader("Assets/Shaders/PBR.vs", "Assets/Shaders/PBR.fs");

	////railgun
	//GameObject* robot = GameObject::Create(this);
	//ModelComponent* mc = new ModelComponent("Assets/Models/railgun", "railgun.obj");
	//robot->AddComponent(mc);
	//RenderComponent* rc = new RenderComponent();
	//robot->AddComponent(rc);
	//TestRotation* rotc = new TestRotation();
	//robot->AddComponent(rotc);
	//robot->transform.position = glm::vec3(0, 0, 0);
	//mc->model.shader = Shader("Assets/Shaders/PBR.vs", "Assets/Shaders/PBR.fs");

	//GameObject* plane = GameObject::Create(this);
	//ModelComponent* planemodel = new ModelComponent("Assets/Models/Plane", "Plane.obj", true);
	//planemodel->model.shader = Shader("Assets/Shaders/PBR.vs", "Assets/Shaders/PBR.fs");
	//plane->AddComponent(planemodel);
	//plane->AddComponent(new RenderComponent());
	//plane->transform.position = glm::vec3(0, -5, 0);

	int count = 8;
	int spacing = 2;
	int x = 0;
	int y = 0;
	for (int i = 0; i < count; i++)
	{
		y = 0;
		for (int j = 0; j < count; j++)
		{

			GameObject* block = GameObject::Create(this);
			ModelComponent* mc = new ModelComponent("Assets/Models/Sphere", "Sphere.obj");
			block->AddComponent(mc);

			RenderComponent* rc = new RenderComponent();
			block->AddComponent(rc);

			block->transform.position = glm::vec3(x - count / 2 - spacing, y - count / 2 - spacing,0);
			mc->model.shader = Shader("Assets/Shaders/PBR_NoTex.vs", "Assets/Shaders/PBR_NoTex.fs");

			mc->model.shader.UseShader();
			mc->model.shader.SetVec3("unidiffuse", glm::vec3(1, 0, 0));
			mc->model.shader.SetFLoat("unimetallic", glm::max((1.0f/count) * j, 0.1f));
			//mc->model.shader.SetFLoat("uniao", glm::max((1.0f / count) * j, 0.1f));
			mc->model.shader.SetFLoat("uniroughness", glm::max((1.0f / count) * i, 0.1f));

			glUseProgram(0);

			y += spacing;
		}
		x += spacing;
	}



}

GameSetup::GameSetup(Window* window)
{
	this->window = window;
}


GameSetup::~GameSetup()
{
}
