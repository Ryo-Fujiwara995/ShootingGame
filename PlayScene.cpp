#include "PlayScene.h"
#include "SpaceShuttle.h"
#include "SpiralEnemy.h"
#include "StraightLineEnemy.h"
#include "Engine/Image.h"
#include "GameSetting.h"
#include "HpBar.h"

#include "Engine/VFX.h"
#include "Engine/SceneManager.h"
#include "Engine/Debug.h"
#include "Engine/Input.h"
#include "Engine/Time.h"

#include "TitleScene.h"
PlayScene::PlayScene(GameObject* parent):GameObject(parent),hPict_(-1)
{
}
void PlayScene::Initialize()
{	
	Instantiate<HpBar>(this);
	// îwåi
	hPict_ = Image::Load("Images\\TitleBack.png");
	//Instantiate<SpaceShuttle>(this);
	player_ = Instantiate<Player>(this);

	
}

void PlayScene::Update()
{

	float dt = Time::GetDeltaTime();
	enemySpawnTimer_ += dt;

	if (enemySpawnTimer_ >= enemySpawnInterval_) {
		enemySpawnTimer_ = 0.0f;

		int randVal = rand() % 2; // 0 or 1

		if (randVal == 0) {
			auto spiralEnemy = Instantiate<SpiralEnemy>(this);
			spiralEnemy->player_ = player_;
			spiralEnemy->Initialize();
		}
		else {
			auto straightEnemy = Instantiate<StraightLineEnemy>(this);
			straightEnemy->player_ = player_;
			straightEnemy->Initialize();
		}
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
