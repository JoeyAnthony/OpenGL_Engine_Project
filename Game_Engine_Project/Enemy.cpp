#include "Enemy.h"
#include "GameObject.h"
#include "GameSetup.h"

void Enemy::init(uint32_t id)
{

}

void Enemy::Update()
{
	glm::vec3 dir = target->transform.position - parent->transform.position;
	dir = Tools::lerp(parent->transform.forward, dir, Tools::DeltaTime());
	float angle =  glm::atan(dir.x, dir.z);
	parent->transform.rotation.y = glm::degrees(angle);
	parent->UpdateTransform();
}

Enemy::Enemy(EnemySpawner * spawner, GameObject* target) : enemySpawner(spawner), target(target)
{

}

Enemy::~Enemy()
{
}
