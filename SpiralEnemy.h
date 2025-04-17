#pragma once
#include "Enemy.h"
#include "Player.h"
/// <summary>
/// �����ڋߌ^�̓G�N���X
/// </summary>
class SpiralEnemy :public Enemy
{
private:
	int hSpiralEnemyDefaultModel_;
	

	float radius_ = 30.0f;
	float angle_ = 0.0f;
	float angularSpeed_ = 1.5f;
	float radialSpeed_ = 5.0f;


	bool enteredProximity_ = false; // �v���C���[�͈͂ɓ�������
	float timeSinceEntered_ = 0.0f; // �o�ߎ���

	const float proximityRadius = 5.0f;
	const float disappearAfter = 2.0f; // �� ��F�����Ă���2�b��ɏ�����
public:
	Player* player_ = nullptr;
	SpiralEnemy(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

