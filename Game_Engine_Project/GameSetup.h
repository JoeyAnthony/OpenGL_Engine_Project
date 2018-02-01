#pragma once
#include <vector>
#include <unordered_map>
#include "GameObject.h"

//#include "Component.h"
#include "CameraComponent.h"
#include "ModelComponent.h"
#include "RenderComponent.h"
#include "ControllerComponent.h"

struct ObjectContainer
{
	std::unordered_map<uint32_t, GameObject> MasterGameObjectList;
	std::unordered_map<uint32_t, CameraComponent*> cameras;
	std::unordered_map<uint32_t, RenderComponent*> drawables;
};

class GameSetup
{
private:

	ObjectContainer objectContainer;
	uint32_t GameObjectCount = 0;
	/**
	* 
	*/
	int NewGameObjectNum();

public:
	/**
	* adds gameobject to the scene list
	*/
	GameObject* AddGameObject(GameObject obj);

	/**
	* adds camera or drawable to renderlists
	*/
	void AddDrawable(RenderComponent* component);
	void AddDrawable(CameraComponent* component);

	void Destroy();

	/**
	* calls Update in every object in the current scene
	*/
	void UpdateScene();

	/**
	* calls LateUpdate in every object in the current scene
	*/
	void LateUpdateScene();

	/**
	* calls FixedUpdate in every object in the current scene
	*/
	void FixedUpdateScene();

	/**
	* Render all GameObjects with a renderer
	*/
	void Render();

	/**
	* Returns the objectcontainer
	*/
	ObjectContainer* GetObjectContainer();


	void CreateScene();

	GameSetup();
	~GameSetup();
};

