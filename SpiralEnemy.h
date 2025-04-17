#pragma once
#include "Enemy.h"
#include "Player.h"
/// <summary>
/// —†ùÚ‹ßŒ^‚Ì“GƒNƒ‰ƒX
/// </summary>
class SpiralEnemy :public Enemy
{
private:
	int hSpiralEnemyDefaultModel_;
	

	float radius_ = 30.0f;
	float angle_ = 0.0f;
	float angularSpeed_ = 1.5f;
	float radialSpeed_ = 5.0f;
public:
	Player* player_ = nullptr;
	SpiralEnemy(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

