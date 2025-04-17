#pragma once
#include "Enemy.h"
#include "Player.h"
/// <summary>
/// 螺旋接近型の敵クラス
/// </summary>
class SpiralEnemy :public Enemy
{
private:
	int hSpiralEnemyDefaultModel_;
	

	float radius_ = 30.0f;
	float angle_ = 0.0f;
	float angularSpeed_ = 1.5f;
	float radialSpeed_ = 5.0f;


	bool enteredProximity_ = false; // プレイヤー範囲に入ったか
	float timeSinceEntered_ = 0.0f; // 経過時間

	const float proximityRadius = 5.0f;
	const float disappearAfter = 2.0f; // ← 例：入ってから2秒後に消える
public:
	Player* player_ = nullptr;
	SpiralEnemy(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

