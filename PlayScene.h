#pragma once
#include "Engine/GameObject.h"

class PlayScene : public GameObject
{
private:
	int hPict_;
public:
	PlayScene(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};