#pragma once
#include "Component.h"

class EnemySpawner;

class Enemy : public Component
{
private:
	EnemySpawner* enemySpawner;
	GameObject* target;

public:
	void init(uint32_t id) override;
	void Update() override;

	Enemy(EnemySpawner* spawner, GameObject* target);
	~Enemy();
};

