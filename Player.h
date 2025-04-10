#pragma once
#include "Engine/GameObject.h"

enum PLAYER_ID {
	PLAYER_ID_DEFAULT = 0,	// �������
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
	PLAYER_ID currentPlayerID_;
	PLAYER_ID nextPlayerID_;
	PLAYER_ID playerState_;
public:
	Player(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
	
};

