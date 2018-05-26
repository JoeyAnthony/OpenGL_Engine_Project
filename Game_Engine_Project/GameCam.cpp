#include "GameCam.h"
#include "GameObject.h"
#include "Tools.h"



void GameCam::CalcTransform()
{
	campos = player->transform.position;
	campos.y = camHeight;
	campos.z += camPlayerZOffset;

	lookdir = glm::normalize(player->transform.position - parent->transform.position);
}

void GameCam::init(uint32_t id)
{
	Component::init(id);
	CalcTransform();
	parent->transform.position = campos;
	parent->transform.forward = lookdir;
}

void GameCam::Update()
{

}

void GameCam::LateUpdate()
{
	CalcTransform();


	parent->transform.position = Tools::lerp(parent->transform.position, campos, Tools::DeltaTime() * followSpeed);
	parent->transform.forward = Tools::lerp(parent->transform.forward, lookdir, Tools::DeltaTime() * followSpeed);

	
}


GameCam::GameCam(GameObject * player)
{
	this->player = player;
}

GameCam::~GameCam()
{
}
