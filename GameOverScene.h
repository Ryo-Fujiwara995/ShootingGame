#pragma once
#include "Engine/GameObject.h"

class GameOverScene : public GameObject
{
private:
	int hGameOverPict_;
	int hGameOverSceneSound_;
public:
	GameOverScene(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};