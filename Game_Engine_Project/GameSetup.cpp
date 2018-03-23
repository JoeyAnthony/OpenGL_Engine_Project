#include "GameSetup.h"

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
	

	//GameObject* block = GameObject::Create(this);
	//ModelComponent* mc = new ModelComponent("Assets/Models/Sphere", "Sphere.obj");
	//block->AddComponent(mc);


	//RenderComponent* rc = new RenderComponent();
	//block->AddComponent(rc);

	//block->transform.position = glm::vec3(0, 0, 0);
	//mc->model.shader = Shader("Assets/Shaders/PBRTest.vs", "Assets/Shaders/PBRTest.fs");


	//GameObject* plane = GameObject::Create(this);
	//ModelComponent* pm = new ModelComponent("Assets/Models/Plane", "Plane.obj");
	//plane->AddComponent(pm);
	//plane->AddComponent(new RenderComponent());
	//pm->model.shader = Shader("Assets/Shaders/Phong.vs", "Assets/Shaders/Phong.fs");
	//plane->transform.position = glm::vec3(0, -2, 0);


	

	int count = 7;
	int spacing = 2;
	int x = 0;
	int y = 0;
	for (int i = 0; i < count; i++)
	{
		y = 0;
		for (int j = 0; j < count; j++)
		{
			//GameObject* block = GameObject::Create(this);
			//ModelComponent* mc = new ModelComponent("Assets/Models/cube2", "cube.obj");
			//block->AddComponent(mc);
			//mc->model.AddTexManual("sculptedfloorboards4_basecolor.png", "texture_diffuse", 0);
			//mc->model.AddTexManual("sculptedfloorboards4_normal.png", "texture_normal", 0);
			//mc->model.AddTexManual("sculptedfloorboards4_height.png", "texture_height", 0);
			//mc->model.AddTexManual("sculptedfloorboards4_metalness.png", "texture_metallic", 0);
			//mc->model.AddTexManual("sculptedfloorboards4_roughness.png", "texture_roughness", 0);
			//mc->model.AddTexManual("sculptedfloorboards4_AO.png", "texture_ambientocclusion", 0);

			//RenderComponent* rc = new RenderComponent();
			//block->AddComponent(rc);

			//block->transform.position = glm::vec3(0, y - count - spacing/2, x - count - spacing / 2);
			//mc->model.shader = Shader("Assets/Shaders/PBR.vs", "Assets/Shaders/PBR.fs");

			GameObject* block = GameObject::Create(this);
			ModelComponent* mc = new ModelComponent("Assets/Models/Sphere", "Sphere.obj");
			block->AddComponent(mc);

			RenderComponent* rc = new RenderComponent();
			block->AddComponent(rc);

			block->transform.position = glm::vec3(0, y - count - spacing / 2, x - count - spacing / 2);
			mc->model.shader = Shader("Assets/Shaders/PBRTest.vs", "Assets/Shaders/PBRTest.fs");

			mc->model.shader.UseShader();
			mc->model.shader.SetFLoat("tmetallic",	glm::max((1.0f/count) * j, 0.1f));
			mc->model.shader.SetFLoat("troughness", glm::max((1.0f / count) * i, 0.1f));
			glUseProgram(0);

			//mc->model.shader.
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
