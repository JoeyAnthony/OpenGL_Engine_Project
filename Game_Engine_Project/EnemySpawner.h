#pragma once
#include "Component.h"
#include "Enemy.h"
#include <vector>
#include "ModelComponent.h"

//class LineRenderer;


class EnemySpawner : public Component
{
private:
	unsigned int wave;
	GameObject* player;
	ModelComponent* enemyModel;
	ModelComponent* bulletModel;
	float boundsDistance = 9.0f;

	void markDefeated(Enemy* enemy);
	glm::vec3 genPosition(float angle, glm::vec3 otherpos, float distance);

public:
	std::vector<GameObject*> aliveEnemies;
	std::vector<GameObject*> defeatedEnemies;

	void spawnEnemy(int enemycount);


	void init(uint32_t id) override;
	void Update() override;
	void freeData() override;

	EnemySpawner(GameObject* player, ModelComponent* enemy, ModelComponent* bullet);
	~EnemySpawner();
};

