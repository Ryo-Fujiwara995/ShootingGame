#include "PlayScene.h"
#include "Player.h"
#include "SpaceShuttle.h"
#include "Enemy.h"
#include "SpiralEnemy.h"
#include "StraightLineEnemy.h"
#include "GameSetting.h"
PlayScene::PlayScene(GameObject* parent)
{
}

void PlayScene::Initialize()
{
	//Instantiate<SpaceShuttle>(this);
	Player * player = Instantiate<Player>(this);
	//Instantiate<Enemy>(this);
	//for (int i = 0; i < SPIRAL_ENEMY_MAX; i++) {
	//	auto spiralEnemy = Instantiate<SpiralEnemy>(this);
	//	spiralEnemy->player_ = player;	// 各敵に共通のPlayerを設定
	//	spiralEnemy->Initialize();		// 各敵にランダムな初期位置を設定
	//}

	for (int j = 0; j < STRAIGHT_LINE_ENEMY_MAX; j++) {
		auto straightLineEnemy = Instantiate<StraightLineEnemy>(this);
		straightLineEnemy->player_ = player;
		straightLineEnemy->Initialize();
	}
}

void PlayScene::Update()
{
	/*


	*/
}

void PlayScene::Draw()
{
}

void PlayScene::Release()
{
}
