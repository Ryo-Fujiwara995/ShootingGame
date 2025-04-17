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
	for (int i = 0; i < 6; i++) {
		auto spiralEnemy = Instantiate<SpiralEnemy>(this);
		spiralEnemy->player_ = player;	// �e�G�ɋ��ʂ�Player��ݒ�
		spiralEnemy->Initialize();		// �e�G�Ƀ����_���ȏ����ʒu��ݒ�
	}
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
