#pragma once
#include "Engine/GameObject.h"

enum PLAYER_ID {
	PLAYER_ID_DEFAULT = 0,	// �������
	PLAYER_ID_SWIM = 1,	// �j��
	PLAYER_ID_FLOAT,	// �ӂ�ӂ�
	PLAYER_ID_MAX
};

class Player :
    public GameObject
{
private:
	int hPlayerModel_;
	int hPlayerSwimmingModel_;
	int hPlayerFloatingModel_;
	PLAYER_ID playerState_;
	bool isRotateRight_;
	float originalRotateRight_;

	bool isRotateLeft_;
	float originalRotateLeft_;
public:
	Player(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
	
	// Player�̃|�W�V�������O�łƂ��Ă��邽�߂Ɏg�p
	DirectX::XMFLOAT3& GetPosition() { return transform_.position_; }
	
};