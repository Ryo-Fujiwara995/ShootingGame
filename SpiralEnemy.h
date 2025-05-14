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
	float radialSpeed_ = 5.0f;

	bool enteredProximity_ = false; // プレイヤー範囲に入ったか
	float timeSinceEntered_ = 0.0f; // プレイヤー範囲に入ってからの時間

	const float proximityRadius = 5.0f; // プレイヤーとの接触範囲
	const float disappearAfter = 2.0f;  // プレイヤー範囲に入ってからの消滅時間
public:
	Player* player_ = nullptr;
	SpiralEnemy(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

