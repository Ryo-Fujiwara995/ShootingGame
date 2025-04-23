#pragma once
#include "Enemy.h"
#include "Player.h"
#include "GameSetting.h"
/// <summary>
/// Player����������܂������i�ޓG�N���X
/// </summary>
class StraightLineEnemy :
    public Enemy
{
private:
	int hStraightLineEnemyModel_;

    bool lockedOn_ = false;
    XMFLOAT3 targetPos_;
    float speed_ = STRAIGHT_LINE_ENEMY_SPEED; // �i�s���x
    float stopRadius_ = STRAIGHT_LINE_ENEMY_STOP_RADIUS; // ���B���a���x
public:
	StraightLineEnemy(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
    Player* player_ = nullptr;
	//�@Player����������A���������_�ł�Player�̃|�W�V�����Ɍ������Ă܂������i�ޓG�N���X������������
};