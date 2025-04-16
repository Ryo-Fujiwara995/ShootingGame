#pragma once
#include "Engine/GameObject.h"

enum PLAYER_ID {
	PLAYER_ID_DEFAULT = 0,	// èâä˙èÛë‘
	PLAYER_ID_SWIM = 1,	// âjÇÆ
	PLAYER_ID_FLOAT,	// Ç”ÇÊÇ”ÇÊ
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
	
};

