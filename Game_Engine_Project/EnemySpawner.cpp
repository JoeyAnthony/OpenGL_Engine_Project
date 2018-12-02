#include "EnemySpawner.h"
#include "GameObject.h"
#include "GameSetup.h"
#include "RenderComponent.h"
#include "ProjectileCannon.h"
#include "CollisionComponent.h"

void EnemySpawner::spawnEnemy(int enemycount)
{
	for (int i = 0; i < enemycount; i++) {
		//calculate a position
		glm::vec3 pos;
		float angle = (350.0f / enemycount * i);
		pos = genPosition(angle, player->transform.position, boundsDistance);
		if (glm::length(pos) > 12.5f)
		{
			pos = genPosition(angle + 70.0f, player->transform.position, boundsDistance);
		}

		//spawn enemy
		GameObject* enemy = GameObject::Create(parent->GetSetup());
		enemy->transform.position = pos;
		enemy->transform.scale = glm::vec3(0.5, 0.5, 0.5);
		enemy->AddComponent(enemyModel);
		enemy->AddComponent(new RenderComponent());
		enemy->AddComponent(new CollisionComponent());
		enemy->AddComponent(new ProjectileCannon(0.7, 9.0, true, bulletModel, {20.0, 12.0, 17.0}));
		enemy->AddComponent(new Enemy(this, player)); //yh I know, templates are better
		aliveEnemies.push_back(enemy);
	}
}

glm::vec3 EnemySpawner::genPosition(float angle, glm::vec3 otherpos, float distance)
{
	glm::vec3 pos;
	pos.x = glm::cos(glm::radians(angle)); pos.z = glm::sin(glm::radians(angle));
	pos = glm::normalize(pos)* distance;
	return pos + otherpos;
}

void EnemySpawner::init(uint32_t id)
{
}

void EnemySpawner::Update()
{
	if (aliveEnemies.size() < 1)
	{
		spawnEnemy(4);
	}
	

}

void EnemySpawner::freeData()
{
}

EnemySpawner::EnemySpawner(GameObject * player, ModelComponent * enemy, ModelComponent * bullet) : player(player), enemyModel(enemy), bulletModel(bullet)
{
}

EnemySpawner::~EnemySpawner()
{
}
