#include "PlayScene.h"
#include "Player.h"
#include "SpaceShuttle.h"
PlayScene::PlayScene(GameObject* parent)
{
}

void PlayScene::Initialize()
{
	Instantiate<SpaceShuttle>(this);
	Instantiate<Player>(this);
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
