#include "GameSetup.h"

#include "CameraComponent.h"
#include "ModelComponent.h"
#include "RenderComponent.h"
#include "TestRotation.h"
#include "CollisionComponent.h"
#include "FreeCam.h"
#include "GameCam.h"
#include "PlayerInput.h"
#include "ProjectileCannon.h"
#include "Light.h"
#include "EnemySpawner.h"


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
		Debug("ERROR: Component NOT Initialized:" << typeid(component).name() << std::endl);
		return;
	}
	objectContainer.drawables.insert(std::pair<uint32_t, RenderComponent*>(component->GetID(), component));
}

void GameSetup::AddDrawable(CameraComponent * component)
{
	if (!component->IsInitialized())
	{
		Debug("Component not Initialized:" << typeid(component).name() << std::endl);
		return;
	}
	objectContainer.cameras.insert(std::pair<uint32_t, CameraComponent*>(component->GetID(), component));
}

uint32_t GameSetup::AddLight(glm::vec3 pos, glm::vec3 color)
{
	objectContainer.lights.insert(std::pair<uint32_t, LightData>(lightcount, LightData{ pos, color }));
	return lightcount++;
}

void GameSetup::RemoveLight(uint32_t id)
{
	objectContainer.lights.erase(id);
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
		it.second.LateUpdate();
	}
	//update uniforms
	DeleteMarkedObjects();
	UpdateShaders(); //debug
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

void GameSetup::DeleteMarkedObjects()
{
	for (auto obj : objectContainer.markedForDeletion)
	{
		obj.second->DeallocateComponents();
		objectContainer.MasterGameObjectList.erase(obj.first);
	}
	objectContainer.markedForDeletion.clear();
}

void GameSetup::UpdateShaders()
{
	UBO.bind();
	int size = objectContainer.lights.size();
	UBO.updateSubBuffer(0, 4, &size);

	//std::vector<glm::vec3> lightspos;
	//std::vector<glm::vec3> lightscolour;
	int index = 0;
	for (auto& p : objectContainer.lights){
		objectContainer.lightspos[index] = glm::vec4(p.second.pos, 0);
		objectContainer.lightscolour[index] = glm::vec4(p.second.color, 0);
		//lightspos.push_back(p.second.pos);
		//lightscolour.push_back(p.second.color);
		index++;
	}
	UBO.updateSubBuffer(16, sizeof(glm::vec4) * 500,  &objectContainer.lightspos[0]); //works but y and z are exchanged in the shader
	UBO.updateSubBuffer(sizeof(glm::vec4) * 500 +16, sizeof(glm::vec4) * 500, &objectContainer.lightscolour[0]); //probably won't work

	UBO.unbind();
}

void GameSetup::CreateScene()
{
	//Camera
	GameObject* camera = GameObject::Create(this);
	camera->name = "mainCam";

	CameraComponent* cc = new CameraComponent(true);
	camera->AddComponent(cc);

	pbrShader = new Shader("Assets/Shaders/PBR.vs", "Assets/Shaders/PBR.fs");
	lineShader = new Shader("Assets/Shaders/LineShader.vs", "Assets/Shaders/LineShader.fs");
	CollisionComponent::lineshader = lineShader;


	UBO = UniformBuffer(GL_MAX_UNIFORM_BLOCK_SIZE, GL_STREAM_DRAW, 0);
	
	//place lights
	int numrounds = 6;
	int dist = 6;
	for (int i = 1; i < numrounds; i++)
	{
		for (int j = 1; j < numrounds; j++)
		{
			GameObject * sceneLight = GameObject::Create(this);
			sceneLight->transform.position = { i*dist - (numrounds/2 * dist), .7, j*-dist + (numrounds/2 * dist) };
			sceneLight->AddComponent(new Light({ 10.0, 12.5, 15.0 }));
		}
	}

	ModelComponent* floormodel = new ModelComponent("Assets/Levels/TopViewShooter/Enviroment/floor", "Floor_Plane.obj", true);
	floormodel->model.shader = pbrShader;

	ModelComponent* playermodel = new ModelComponent("Assets/Levels/TopViewShooter/Characters/player", "Player.obj", true);
	playermodel->model.shader = pbrShader;

	ModelComponent* bulletModel = new ModelComponent("Assets/Levels/TopViewShooter/Enviroment/bullet", "bullet.obj", true);
	bulletModel->model.shader = pbrShader;

	ModelComponent* chestmodel = new ModelComponent("Assets/Models/chestdavy", "Chest_low_Unwrapped.obj", true);
	chestmodel->model.shader = pbrShader;

	ModelComponent* enemymodel = new ModelComponent("Assets/Levels/TopViewShooter/Characters/enemyrect", "Enemy_Rectangle.obj", true);
	enemymodel->model.shader = pbrShader;

	float height = 0.4455f;
	
	GameObject* chest = GameObject::Create(this);
	chest->AddComponent(chestmodel);
	chest->AddComponent(new RenderComponent());
	chest->transform.position = glm::vec3(0, 1.5, 0);
	chest->transform.rotation = glm::vec3(0, 90, 0);

	GameObject* floor = GameObject::Create(this);
	floor->AddComponent(floormodel);
	floor->AddComponent(new RenderComponent());
	floor->transform.position = glm::vec3();
	floor->AddComponent(new CollisionComponent());

	GameObject* player = GameObject::Create(this);
	player->AddComponent(playermodel);
	player->AddComponent(new RenderComponent());
	player->transform.scale = glm::vec3(0.2, 0.2, 0.2);
	player->transform.position = glm::vec3(0, height, 0);
	player->AddComponent(new PlayerInput(cc));
	player->AddComponent(new ProjectileCannon(0.3f, 20.0,false, bulletModel, {10.0, 27.0, 14.0}));
	player->AddComponent(new CollisionComponent());

	GameObject* enemySpawner = GameObject::Create(this);
	EnemySpawner* spawn = new EnemySpawner(player, enemymodel, bulletModel);
	enemySpawner->AddComponent(spawn);
	
	camera->AddComponent(new GameCam(player)); //add gamecam to camera with player ref
	//camera->AddComponent(new FreeCam());	

}

GameSetup::GameSetup(Window* window)
{
	this->window = window;
}


GameSetup::~GameSetup()
{
}
