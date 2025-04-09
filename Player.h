#pragma once
#include "Engine/GameObject.h"
class Player :
    public GameObject
{
private:
	int hPlayerModel_;
	int hPlayerSwimmingModel_;
public:
	Player(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

