#pragma once
#include "Engine/GameObject.h"

enum PLAYER_ID {
	PLAYER_ID_STANDBY = 0,	// �ҋ@���
	PLAYER_ID_SWIM = 1,	// �j��
	PLAYER_ID_FLOAT	// �ӂ�ӂ�
};

class Player :
    public GameObject
{
private:
	int hPlayerModel_;
	int hPlayerSwimmingModel_;
	int hPlayerFloatingModel_;
public:
	Player(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

