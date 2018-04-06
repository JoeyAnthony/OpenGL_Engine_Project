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


	GameObject* plane = GameObject::Create(this);
	ModelComponent* pm = new ModelComponent("Assets/Models/Plane", "Plane.obj");
	plane->AddComponent(pm);
	plane->AddComponent(new RenderComponent());
	pm->model.shader = Shader("Assets/Shaders/Phong.vs", "Assets/Shaders/Phong.fs");
	plane->transform.position = glm::vec3(0, -2, 0);

	//GameObject* robot = GameObject::Create(this);
	//ModelComponent* mc = new ModelComponent("Assets/Models/Robot", "model.dae");
	//robot->AddComponent(mc);
	//mc->model.AddTexManual("/textures/default_albedo.jpg", "texture_diffuse", 0);
	//mc->model.AddTexManual("/textures/default_normal.jpg", "texture_normal", 0);
	////mc->model.AddTexManual("/textures/default_emissive.jpg", "texture_height", 0);
	//mc->model.AddTexManual("/textures/default_metallic.jpg", "texture_metallic", 0);
	//mc->model.AddTexManual("/textures/default_roughness.jpg", "texture_roughness", 0);
	//mc->model.AddTexManual("/textures/default_AO.jpg", "texture_ambientocclusion", 0);

	//RenderComponent* rc = new RenderComponent();
	//robot->AddComponent(rc);

	//TestRotation* rotc = new TestRotation();
	//robot->AddComponent(rotc);


	//robot->transform.position = glm::vec3(0, 0, 0);
	//mc->model.shader = Shader("Assets/Shaders/PBR.vs", "Assets/Shaders/PBR.fs");


	

	int count = 1;
	int spacing = 2;
	int x = 0;
	int y = 0;
	for (int i = 0; i < count; i++)
	{
		y = 0;
		for (int j = 0; j < count; j++)
		{
			GameObject* block = GameObject::Create(this);
			ModelComponent* mc = new ModelComponent("Assets/Models/cube2", "Sphere.obj");
			block->AddComponent(mc);
			mc->model.AddTexManual("sculptedfloorboards4_basecolor.png", "texture_diffuse", 0);
			mc->model.AddTexManual("sculptedfloorboards4_normal.png", "texture_normal", 0);
			mc->model.AddTexManual("sculptedfloorboards4_height.png", "texture_height", 0);
			mc->model.AddTexManual("sculptedfloorboards4_metalness.png", "texture_metallic", 0);
			mc->model.AddTexManual("sculptedfloorboards4_roughness.png", "texture_roughness", 0);
			mc->model.AddTexManual("sculptedfloorboards4_AO.png", "texture_ambientocclusion", 0);

			RenderComponent* rc = new RenderComponent();
			block->AddComponent(rc);

			block->transform.position = glm::vec3(0, 0, 0);
			mc->model.shader = Shader("Assets/Shaders/PBR.vs", "Assets/Shaders/PBR.fs");

			//GameObject* block = GameObject::Create(this);
			//ModelComponent* mc = new ModelComponent("Assets/Models/Sphere", "Sphere.obj");
			//block->AddComponent(mc);

			//RenderComponent* rc = new RenderComponent();
			//block->AddComponent(rc);

			//block->transform.position = glm::vec3(x - count / 2 - spacing, y - count / 2 - spacing,0);
			//mc->model.shader = Shader("Assets/Shaders/PBR_NoTex.vs", "Assets/Shaders/PBR_NoTex.fs");

			//mc->model.shader.UseShader();
			//mc->model.shader.SetVec3("unidiffuse", glm::vec3(1, 0, 0));
			//mc->model.shader.SetFLoat("unimetallic", glm::max((1.0f/count) * j, 0.1f));
			////mc->model.shader.SetFLoat("uniao", glm::max((1.0f / count) * j, 0.1f));
			//mc->model.shader.SetFLoat("uniroughness", glm::max((1.0f / count) * i, 0.1f));

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
