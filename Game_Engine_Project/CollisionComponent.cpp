#include "CollisionComponent.h"
#include "GameObject.h"
#include "GameSetup.h"
#include <unordered_map>
#include <glm\gtx\intersect.hpp>

Shader* CollisionComponent::lineshader;

void CollisionComponent::Render(CameraComponent * cam)
{
//#ifdef _DEBUG
	if(Tools::debug)
		lines->Draw(cam);
//#endif // DEBUG
}

void CollisionComponent::init(uint32_t id)
{
	modelcmp = parent->GetComponent<ModelComponent>();
	if (modelcmp != nullptr)
		bounds = modelcmp->model.getBounds();
	else
	{
		bounds.maxBounds = glm::vec3(0.5, 0.5, 0.5);
		bounds.minBounds = glm::vec3(-0.5, -0.5, -0.5);
	}

//#ifdef _DEBUG
	if(/*Tools::debug &&*/ lines == nullptr)
		lines = new LineRenderer(bounds);
//#endif // DEBUG

	Component::init(id);
	parent->GetSetup()->AddDrawable(this);
}

void CollisionComponent::Update()
{
	
	glm::vec3 push;
	checkCollision(push);
	
	parent->transform.position += push;

	lastTransform = parent->transform;

	checkCollision();

//#ifdef _DEBUG
	//if (Tools::debug)
		lines->transform = parent->transform;	
//#endif // DEBUG
}

float CollisionComponent::smallestOverlap(float posaxis, float negaxis)
{
	float pos = glm::abs(posaxis);
	float neg = glm::abs(negaxis);

	if (pos < neg)
		return posaxis;
	else 
		return negaxis;
}

glm::vec3 CollisionComponent::largestInVec(glm::vec3 vec)
{
	glm::vec3 largest = vec;
	if (glm::abs(largest.x) > glm::abs(largest.y))
	{
		largest.y = 0;
		if (glm::abs(largest.x) > glm::abs(largest.z))
			largest.z = 0;
		else
			largest.x = 0;
	}
	else
	{
		largest.x = 0;
		if (glm::abs(largest.y) > glm::abs(largest.z))
			largest.z = 0;
		else
			largest.y = 0;
	}
	return largest;
}

bool CollisionComponent::checkCollision(glm::vec3& push)
{
	//check collisions if not a static object
	bool collision = false;
	glm::vec3 returnvec;

	if (!isStatic)
	{
		std::unordered_map<uint32_t, GameObject>* map = &parent->GetSetup()->GetObjectContainer()->MasterGameObjectList;

		for (auto obj = map->begin(); obj != map->end(); ++obj)
		{
			//own bounds
			Bounds obounds = bounds;
			obounds.maxBounds *= parent->transform.scale;
			obounds.minBounds *= parent->transform.scale;

			obounds.maxBounds += parent->transform.position;
			obounds.minBounds += parent->transform.position;

			//other bounds
			ModelComponent* m = obj->second.GetComponent<ModelComponent>();
			if (m == nullptr)
				continue;
			if (m->parent->GetID() == parent->GetID())
				continue;

			Bounds mbounds = m->model.getBounds();
			mbounds.maxBounds *= m->parent->transform.scale;
			mbounds.minBounds *= m->parent->transform.scale;

			mbounds.maxBounds += m->parent->transform.position;
			mbounds.minBounds += m->parent->transform.position;

			

			//if there is collision
			if (collide(obounds, mbounds))
			{
				////langste vector teruggeven
				//overlap = lastTransform.position - parent->transform.position;
				//overlap = largestInVec(overlap);


				glm::vec3 direction = glm::normalize( parent->transform.position - lastTransform.position);
				glm::vec3 origin = lastTransform.position;

				HitPlane hits[6];


				//top plane
				float topdistance;
				bool tophit = glm::intersectRayPlane(origin, direction, m->parent->transform.position + mbounds.maxBounds.y, parent->transform.up, topdistance);
				hits[0] = HitPlane{ tophit, topdistance, glm::normalize(parent->transform.up) };

				//bottom plane
				float bottomdistance;
				bool bottomhit = glm::intersectRayPlane(origin, direction, m->parent->transform.position + mbounds.minBounds.y, -parent->transform.up, bottomdistance);
				hits[1] = HitPlane{ bottomhit, bottomdistance, glm::normalize(-parent->transform.up)};


				//front plane
				float frontdistance;
				bool fronthit = glm::intersectRayPlane(origin, direction, m->parent->transform.position + mbounds.minBounds.z, parent->transform.forward, frontdistance);
				hits[2] = HitPlane{ fronthit, frontdistance, glm::normalize(parent->transform.forward) };


				//back plane
				float backdistance;
				bool backhit = glm::intersectRayPlane(origin, direction, m->parent->transform.position + mbounds.maxBounds.z, -parent->transform.forward, backdistance);
				hits[3] = HitPlane{ backhit, backdistance, glm::normalize(-parent->transform.forward) };


				//Left plane
				float leftdistance;
				bool lefthit = glm::intersectRayPlane(origin, direction, m->parent->transform.position + mbounds.minBounds.x, -parent->transform.right, leftdistance);
				hits[4] = HitPlane{ lefthit, leftdistance, glm::normalize(-parent->transform.right) };


				//Right plane
				float rightdistance;
				bool righthit = glm::intersectRayPlane(origin, direction, m->parent->transform.position + mbounds.maxBounds.x, parent->transform.right, rightdistance);
				hits[5] = HitPlane{ righthit, rightdistance, glm::normalize(parent->transform.right) };

				int hit = 0;
				for (int i = 0; i < sizeof(hits) / sizeof(HitPlane); i++)
				{
					if (hits[i].hit)
					{
						if (glm::abs(hits[i].distance) <= glm::abs(hits[hit].distance))
						{
							hit = i;
						}
					}
				}


				returnvec = (lastTransform.position - parent->transform.position) * glm::abs(hits[hit].normal);
				collision = true;

			}
		}


	}
	push = returnvec;
		return collision;
}

void CollisionComponent::checkCollision()
{
	std::unordered_map<uint32_t, GameObject>* map = &parent->GetSetup()->GetObjectContainer()->MasterGameObjectList;

	for (auto obj = map->begin(); obj != map->end(); ++obj)
	{ 
		lines->color = { 0, 1, 0 };
		if (obj->second.ID == parent->ID)
			continue;
		ModelComponent* m = obj->second.GetComponent<ModelComponent>();
		if (m == nullptr)
			continue;

		if (obj->second.ID == excludeID)
			continue;

		if (collide(bounds * parent->transform.scale + parent->transform.position, m->model.getBounds() * obj->second.transform.scale + obj->second.transform.position))
		{
			lines->color = { 1, 0, 0 };

			parent->OnCollision();
			break;
		}
	}
}


bool CollisionComponent::collide(Bounds obounds, Bounds mbounds)
{
	//box collision
	if (obounds.maxBounds.x >= mbounds.minBounds.x &&
		obounds.minBounds.x <= mbounds.maxBounds.x &&

		obounds.maxBounds.y >= mbounds.minBounds.y &&
		obounds.minBounds.y <= mbounds.maxBounds.y &&

		obounds.maxBounds.z >= mbounds.minBounds.z &&
		obounds.minBounds.z <= mbounds.maxBounds.z)
	{

		return true;
	}
	return false;
}

void CollisionComponent::freeData()
{
	parent->GetSetup()->GetObjectContainer()->drawables.erase(GetID());
//#ifdef _DEBUG
	//if (Tools::debug)
		delete lines;
//#endif // DEBUG
}

CollisionComponent::CollisionComponent()
{
	
}

CollisionComponent::CollisionComponent(LineRenderer* lr)
{
	lines = new LineRenderer(*lr);
}


CollisionComponent::~CollisionComponent()
{
}
