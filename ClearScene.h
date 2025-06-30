#pragma once
#include "Engine/GameObject.h"

class ClearScene : public GameObject
{
private:
	int hClearPict_;
	int hClearSceneSound_;
public:
	ClearScene(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};