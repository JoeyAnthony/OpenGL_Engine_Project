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
	


	GameObject* block = GameObject::Create(this);
	ModelComponent* mc = new ModelComponent();
	block->AddComponent(mc);
	
	RenderComponent* rc = new RenderComponent();
	block->AddComponent(rc);

	block->transform.position = glm::vec3(-2, 0, -3);
	mc->addShader("PhongShader.vs", "PhongShader.fs");
	mc->addTexture("texture1", "Assets/Textures/lena.png");
	mc->addTexture("texture1", "Assets/Textures/godzilla.jpg");


	GameObject* block2 = GameObject::Create(this);
	ModelComponent* mc2 = new ModelComponent();
	block2->AddComponent(mc2);

	RenderComponent* rc2 = new RenderComponent();
	block2->AddComponent(rc2);

	block2->transform.position = glm::vec3(2, 0, -3);



}

GameSetup::GameSetup()
{
}


GameSetup::~GameSetup()
{
}
