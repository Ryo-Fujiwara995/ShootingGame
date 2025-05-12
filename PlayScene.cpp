#include "PlayScene.h"
#include "Player.h"
#include "SpaceShuttle.h"
#include "SpiralEnemy.h"
#include "StraightLineEnemy.h"
#include "Engine/Image.h"
#include "GameSetting.h"

#include "Engine/VFX.h"
#include "Engine/SceneManager.h"
#include "Engine/Debug.h"
#include "Engine/Input.h"

#include "TitleScene.h"
PlayScene::PlayScene(GameObject* parent):GameObject(parent),hPict_(-1)
{
}

void PlayScene::Initialize()
{	
	// 背景
	hPict_ = Image::Load("Images\\space.png");
	 Instantiate<SpaceShuttle>(this);
	Player * player = Instantiate<Player>(this);
	
	//背景に星を追加
	EmitterData  starEffect;
	starEffect.textureFileName = "Paticle\\flashC_Y.png";
	starEffect.position = XMFLOAT3(0.0f, 5.0f, 0.0f); // 中央の空中あたり
	starEffect.positionRnd = XMFLOAT3(3.0f, 1.0f, 3.0f); // ランダムにばらまく範囲
	starEffect.size = XMFLOAT2(0.2f, 0.2f); // 小さめ
	starEffect.sizeRnd = XMFLOAT2(0.5f, 0.5f); // サイズのばらつき
	starEffect.color = XMFLOAT4(1, 1, 1, 1); // 白色
	starEffect.deltaColor = XMFLOAT4(0, 0, 0, -0.05f); // 徐々に透明に
	starEffect.lifeTime = 30; // 寿命：30フレーム
	starEffect.delay = 5; // 5フレームごとに発生
	starEffect.number = 1; // 毎回1個発生
	starEffect.isBillBoard = true; // ビルボードで描画
	VFX::Start(starEffect);


	// 10秒ごとにどちらかを生成する予定
	for (int i = 0; i < SPIRAL_ENEMY_MAX; i++) {
		auto spiralEnemy = Instantiate<SpiralEnemy>(this);
		spiralEnemy->player_ = player;	// 各敵に共通のPlayerを設定
		spiralEnemy->Initialize();		// 各敵にランダムな初期位置を設定
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
