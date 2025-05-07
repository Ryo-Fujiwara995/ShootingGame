#include "PlayScene.h"
#include "Player.h"
#include "SpaceShuttle.h"
#include "SpiralEnemy.h"
#include "StraightLineEnemy.h"
#include "Engine/Image.h"
#include "GameSetting.h"

#include "Engine/SceneManager.h"
#include "Engine/Debug.h"
#include "Engine/Input.h"

#include "TitleScene.h"
PlayScene::PlayScene(GameObject* parent):GameObject(parent),hPict_(-1)
{
}

void PlayScene::Initialize()
{
	// ”wŒi
	hPict_ = Image::Load("Images\\space.png");
	 Instantiate<SpaceShuttle>(this);
	Player * player = Instantiate<Player>(this);

	// 10•b‚²‚Æ‚É‚Ç‚¿‚ç‚©‚ğ¶¬‚·‚é—\’è
	for (int i = 0; i < SPIRAL_ENEMY_MAX; i++) {
		auto spiralEnemy = Instantiate<SpiralEnemy>(this);
		spiralEnemy->player_ = player;	// Še“G‚É‹¤’Ê‚ÌPlayer‚ğİ’è
		spiralEnemy->Initialize();		// Še“G‚Éƒ‰ƒ“ƒ_ƒ€‚È‰ŠúˆÊ’u‚ğİ’è
	}

	//for (int j = 0; j < STRAIGHT_LINE_ENEMY_MAX; j++) {
	//	auto straightLineEnemy = Instantiate<StraightLineEnemy>(this);
	//	straightLineEnemy->player_ = player;
	//	straightLineEnemy->Initialize();
	//}
}

void PlayScene::Update()
{
}

void PlayScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

void PlayScene::Release()
{
}
