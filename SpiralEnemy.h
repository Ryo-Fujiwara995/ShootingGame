#pragma once
#include "Player.h"
#include "Engine/GameObject.h"
#include "GameSetting.h"
/// <summary>
/// �����ڋߌ^�̓G�N���X
/// </summary>
class SpiralEnemy:public GameObject
{
private:
	int hSpiralEnemyDefaultModel_;
	float angle_ = 0.0f;
	float angularSpeed_ = 1.5f;
	float radius_ = 30.0f;
	float radialSpeed_ = 5.0f;

	bool enteredProximity_ = false; // �v���C���[�͈͂ɓ�������
	float timeSinceEntered_ = 0.0f;

	const float proximityRadius = 5.0f;
	const float disappearAfter = 2.0f;
public:
	Player* player_ = nullptr;
	SpiralEnemy(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

