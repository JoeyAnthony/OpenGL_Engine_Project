#include "GameObject.h"
#include "Component.h"
#include "RenderComponent.h"
#include "CameraComponent.h"
#include "GameSetup.h"

uint32_t GameObject::NewComponentNum()
{
	int newID = (ID << 3) + ++ComponentCount;
	return  newID;
}

GameObject* GameObject::Create(GameSetup *game)
{
	GameObject obj(game);
	return game->AddGameObject(obj);
}

void GameObject::AddComponent(Component* component)
{
	component->parent = this;

	if (typeid(*component) == typeid(RenderComponent))
	{
		RenderComponent* rendercomponent = (RenderComponent*)component;
		rendercomponent->init(NewComponentNum());
	}
	else if (typeid(*component) == typeid(CameraComponent))
	{
		CameraComponent* cameracomponent = (CameraComponent*)component;
		cameracomponent->init(NewComponentNum());
	}
	else
	{
		component->init(NewComponentNum());
	}

	ComponentList.push_back(component);

}

//template <typename T>
//template T* GameObject::GetComponent<ModelComponent>();

void GameObject::Update()
{
	for (Component* obj : ComponentList)
	{
		obj->Update();
	}

	//for (std::vector<Component*>::iterator it = ComponentList.begin(); it != ComponentList.end(); ++it)
	//{
	//	
	//}
}

void GameObject::LateUpdate()
{
	for (Component* obj : ComponentList)
	{
		obj->LateUpdate();
	}

	//for (auto it = ComponentList.begin(); it != ComponentList.end(); ++it)
	//{
	//	it->Update();
	//}
}

void GameObject::FixedUpdate()
{
	for (Component* obj : ComponentList)
	{
		obj->FixedUpdate();
	}

	//for (auto it = ComponentList->begin(); it != ComponentList->end(); ++it)
	//{
	//	//it->second.FixedUpdate();
	//	it->second->LateUpdate();
	//}
}

void GameObject::init(uint32_t id)
{
	ID = id;
	Initialized = true;
}

GameSetup* GameObject::GetSetup()
{
	return ParentSetup;
}

uint32_t GameObject::GetID()
{
	return ID;
}

const bool GameObject::IsInitialized()
{
	return Initialized;
}

GameObject::GameObject(const GameObject& obj)
{
	ComponentList = obj.ComponentList;
	ParentSetup = obj.ParentSetup;
	Position = obj.Position;
	Rotation = obj.Rotation;
	name = obj.name;
	transform = obj.transform;
}

GameObject::GameObject(GameSetup* setup)
{
	ParentSetup = setup;
}

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}
