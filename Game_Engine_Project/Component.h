#pragma once
#include <iostream>
#include "Tools.h"

#include <glm\glm.hpp>
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"


class GameObject;


class Component
{
private:
	/*
	* Component id
	*/
	uint32_t ID = 0;
	/*
	* Initialized or not
	*/
	bool Initialized = false;

protected:
	//pointer to component list
	//needs different states


public:
	GameObject* parent;
	const uint32_t GetID();
	/**
	* Returns initialized bool
	*/
	const bool IsInitialized();

	virtual void Update();
	virtual void LateUpdate();
	virtual void FixedUpdate();
	//virtual void Render();
	virtual void init(uint32_t id);

	Component();
};


