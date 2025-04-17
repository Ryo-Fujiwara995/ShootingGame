#include "PlayScene.h"
#include "Player.h"
#include "SpaceShuttle.h"
#include "Enemy.h"
#include "SpiralEnemy.h"
PlayScene::PlayScene(GameObject* parent)
{
}

void PlayScene::Initialize()
{
	//Instantiate<SpaceShuttle>(this);
	Player * player = Instantiate<Player>(this);
	//Instantiate<Enemy>(this);
	SpiralEnemy * spiralEnemy = Instantiate<SpiralEnemy>(this);
	spiralEnemy->player_ = player;
	spiralEnemy->Initialize();
	
}

void PlayScene::Update()
{

}

void PlayScene::Draw()
{
}

void PlayScene::Release()
{
}
