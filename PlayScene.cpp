#include "PlayScene.h"
#include "Player.h"
#include "SpaceShuttle.h"
#include "Enemy.h"
#include "SpiralEnemy.h"
#include "StraightLineEnemy.h"
#include "Engine/Image.h"
#include "GameSetting.h"

#include "Engine/Debug.h"
#include "Engine/Input.h"
PlayScene::PlayScene(GameObject* parent):GameObject(parent),hPict_(-1)
{
}

void PlayScene::Initialize()
{
	// 背景
	hPict_ = Image::Load("Images\\space.png");

	//Instantiate<SpaceShuttle>(this);
	Player * player = Instantiate<Player>(this);
	//Instantiate<Enemy>(this);

	// 10秒ごとにどちらかを生成する予定
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

	// GamePadの○○キーが押されたら、DebugLogを出力する -> ZR ZL を確認したい
	if (Input::IsPadButtonDown()) {
		Debug::Log("Game Pad Log Pushed Success!!");
	}
}

void PlayScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

void PlayScene::Release()
{
}
