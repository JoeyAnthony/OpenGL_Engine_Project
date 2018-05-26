#pragma once
#include <vector>
#include <unordered_map>
#include "GameObject.h"

#include "Window.h"

class CameraComponent;
class RenderComponent;


struct ObjectContainer
{
	std::unordered_map<uint32_t, GameObject> MasterGameObjectList;
	std::unordered_map<uint32_t, CameraComponent*> cameras;
	std::unordered_map<uint32_t, RenderComponent*> drawables;
	std::unordered_map<uint32_t, GameObject*> markedForDeletion;
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
	/*
	* maincam ID
	*/
	uint32_t mainCamID;

	/**
	* adds gameobject to the scene list
	*/
	GameObject* AddGameObject(GameObject obj);

	/**
	* Window the GameSetup is being rendered is
	*/
	Window* window;

	/**
	* adds camera or drawable to renderlists
	*/
	void AddDrawable(RenderComponent* component);
	void AddDrawable(CameraComponent* component);
	//void AddDrawable(CollisionComponent * component);

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
	* Remove marked objects
	*/
	void DeleteMarkedObjects();

	/**
	* Returns the objectcontainer
	*/
	ObjectContainer* GetObjectContainer();


	void CreateScene();

	GameSetup(Window* window);
	~GameSetup();
};

