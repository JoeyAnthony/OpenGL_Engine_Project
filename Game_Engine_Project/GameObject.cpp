#include "GameObject.h"
#include "Component.h"
#include "RenderComponent.h"
#include "CameraComponent.h"
#include "GameSetup.h"
#include <glm/gtc/constants.hpp>
#include "Tools.h"

uint32_t GameObject::NewComponentNum()
{
	int newID = (ID << 3) + ++ComponentCount;
	return  newID;
}

void GameObject::DeallocateComponents()
{
	for (auto comp : ComponentList)
	{
		if (!dynamic_cast<ModelComponent*>(comp))
		{
			comp->freeData();
			delete comp;
		}
	}
	ComponentList.clear();
}

void GameObject::UpdateTransform()
{
	//calculate right vector
	glm::vec3 fvec = glm::vec3{ glm::normalize(glm::vec4(0, 0, -1, 1) * transform.modelMatrix) };
	fvec.z *= -1;
	transform.right = glm::cross(transform.forward, transform.up);

	transform.forward = glm::normalize(fvec);

	////calculate forward vector
	//glm::vec3 front;
	//front.x = cos(glm::radians(transform.rotation.x)) * cos(glm::radians(transform.rotation.y));
	//front.y = sin(glm::radians(transform.rotation.x));
	//front.z = cos(glm::radians(transform.rotation.x)) * sin(glm::radians(transform.rotation.y));
	//transform.forward = glm::normalize(front);



}

GameObject* GameObject::Create(GameSetup *game)
{
	GameObject obj(game);
	return game->AddGameObject(obj);
}

void GameObject::Destroy()
{
		std::pair<uint32_t, GameObject*> pair(ID, &GetSetup()->GetObjectContainer()->MasterGameObjectList[ID]);
		GetSetup()->GetObjectContainer()->markedForDeletion.insert(pair);
}

void GameObject::setForward(glm::vec3 dir)
{
	transform.rotation.y = std::atan2( dir.z, dir.y) * 180 / glm::pi<GLfloat>();
	Debug("deg: " << transform.rotation.y << " x: " << dir.x << " y: " << dir.y << " z: " << dir.z << std::endl);
	//transform.rotation.x = -std::asin(dir.y);
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
}

void GameObject::LateUpdate()
{
	for (Component* obj : ComponentList)
	{
		obj->LateUpdate();
	}

}

void GameObject::FixedUpdate()
{
	for (Component* obj : ComponentList)
	{
		obj->FixedUpdate();
	}

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
