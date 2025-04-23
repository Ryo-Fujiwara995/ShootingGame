#pragma once
#include "Enemy.h"
#include "Player.h"
#include "GameSetting.h"
/// <summary>
/// �����ڋߌ^�̓G�N���X
/// </summary>
class SpiralEnemy :public Enemy
{
private:
	int hSpiralEnemyDefaultModel_;
	float angle_ = SPIRAL_ENEMY_ANGLE;
	float angularSpeed_ = SPIRAL_ENEMY_ANGULAR_SPEED;
	float radius_ = SPIRAL_ENEMY_RADIUS;
	float radialSpeed_ = SPIRAL_ENEMY_RADIAL_SPEED;

	bool enteredProximity_ = false; // �v���C���[�͈͂ɓ�������
	float timeSinceEntered_ = SPIRAL_ENEMY_TIME_SINCE_ENTERED;

	const float proximityRadius = SPIRAL_ENEMY_PROXIMITY_RADIUS;
	const float disappearAfter = SPIRAL_ENEMY_DISAPPEAR_AFTER;
public:
	Player* player_ = nullptr;
	SpiralEnemy(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

