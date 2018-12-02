#pragma once
#include <vector>
#include <unordered_map>

#include "Shader.h"
#include "UniformBuffer.h"

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
	std::unordered_map<uint32_t, LightData> lights;
	glm::vec4 lightspos[500];
	glm::vec4 lightscolour[500];
};

class GameSetup
{
private:

	Shader * pbrShader;
	Shader * lineShader;
	ObjectContainer objectContainer;
	uint32_t GameObjectCount = 0;
	uint32_t lightcount = 0;
	/**
	* 
	*/
	int NewGameObjectNum();

	UniformBuffer UBO;


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

	/*
	*Add light to the scene
	*/
	uint32_t AddLight(glm::vec3 pos, glm::vec3 color);

	/*
	*Remove light
	*/
	void RemoveLight(uint32_t id);

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
	* Updates UBOs
	*/
	void UpdateShaders();

	/**
	* Returns the objectcontainer
	*/
	ObjectContainer* GetObjectContainer();


	void CreateScene();

	GameSetup(Window* window);
	~GameSetup();
};

