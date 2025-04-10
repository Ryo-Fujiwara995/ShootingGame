#pragma once
#include "Engine/GameObject.h"

enum PLAYER_ID {
	PLAYER_ID_STANDBY = 0,	// ë“ã@èÛë‘
	PLAYER_ID_SWIM = 1,	// âjÇÆ
	PLAYER_ID_FLOAT	// Ç”ÇÊÇ”ÇÊ
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

