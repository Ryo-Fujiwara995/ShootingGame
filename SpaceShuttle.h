#pragma once
#include "Engine/GameObject.h"
class SpaceShuttle :
    public GameObject
{
private:
	int hSpaceShuttleModel_;
public:
	SpaceShuttle(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

