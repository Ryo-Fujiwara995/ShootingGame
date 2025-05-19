#pragma once
#include "Player.h"
#include "Engine/GameObject.h"
#include "GameSetting.h"
/// <summary>
/// 螺旋接近型の敵クラス
/// </summary>
class SpiralEnemy:public GameObject
{
private:
	int hSpiralEnemyDefaultModel_;
	float angle_ = 0.0f;
	float angularSpeed_ = 1.5f;
	float radius_ = 30.0f;
	float radialSpeed_ = 5.0f;// drioai 

	bool enteredProximity_ = false; // プレイヤー範囲に入ったか
	float timeSinceEntered_ = 0.0f; // プレイヤー範囲に入ってからの時間

	const float proximityRadius = 5.0f; // プレイヤーとの接触範囲
	const float disappearAfter = 2.0f;  // プレイヤー範囲に入ってからの消滅時間

	float verticalAmplitude_ = 1.0f;     // 上下の振れ幅
	float verticalFrequency_ = 2.0f;     // 上下の速さ（周期）
	float verticalPhase_ = 0.0f;         // 位相（初期値）

	XMFLOAT3 targetPos_{}; // ロックオン位置
public:
	Player* player_ = nullptr;
	SpiralEnemy(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

