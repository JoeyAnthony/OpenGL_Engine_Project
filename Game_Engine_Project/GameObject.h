#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>
#include <typeindex>
#include <typeinfo>

#include "Vec.h"

#include <glm\glm.hpp>
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

class Component;
class GameSetup;

class GameObject
{
private:
	/**
	* list of all components in this gameobject
	might change it to unordered map
	*/
	std::vector<Component*> ComponentList;

	
	/**
	* Gamesetup that owns this GameObject 
	*/
	GameSetup* ParentSetup;

	/*
	* Unique ID of this GameObject
	*/
	uint32_t ID;

	/*
	* component number, used in NewComponentNum
	*/
	uint32_t ComponentCount = 0;

	/*
	* Generates component id
	*/
	uint32_t NewComponentNum();

	/*
	* Initialized or not
	*/
	bool Initialized = false;


protected:

public:
	struct Transform
	{
		//tranformations
		glm::vec3 position = glm::vec3(0, 0, 0);
		glm::vec3 rotation = glm::vec3(0, 0, 0);
		glm::vec3 scale = glm::vec3(1, 1, 1);

		glm::vec3 forward = glm::vec3(0, 0, 0);
		glm::vec3 right = glm::vec3(0, 0, 0);
		glm::vec3 up = glm::vec3(0, 1, 0);
	};
	Transform transform;

	/**
	*	name of gameobject
	*/
	std::string name;
	/**
	*	position of this gameobject
	*/
	Vec3f Position;

	/**
	* rotation of this gameobject
	*/
	Vec3f Rotation;

	/**
	*
	*/
	static GameObject* Create(GameSetup *game);

	/**
	*
	*/
	void AddComponent(Component* component);

	/**
	* garbage collector : mark object for deletion.wil later be deleted
	* also delete rendercomponent here
	*/
	//void DeleteComponent();

	/**
	* search for a component in the corresponding gameobject with the same ID
	*/
	//Component* GetComponent(int type);
	
	template <typename T>
	T* GetComponent()
	{
		for (Component* c : ComponentList)
		{
			if (typeid(T) == typeid(*c))
				return dynamic_cast<T*>(c);
		}

		return nullptr;
	}

	/**
	*update this gameobject all components
	*/
	virtual void Update();

	/**
	* late update this gameobject all components
	*/
	virtual void LateUpdate();

	/**
	* fixed update this gameobject all components
	*/
	virtual void FixedUpdate();

	/**
	* Initializes GameObject and all components
	*/
	void init(uint32_t id);

	/**
	* Returns the setup that holds this GameObject
	*/
	 GameSetup* GetSetup();

	 /**
	 * Returns initialized bool
	 */
	 const bool IsInitialized();

 GameObject(const GameObject& obj);
	GameObject(GameSetup* setup);
	GameObject();
	~GameObject();
};

