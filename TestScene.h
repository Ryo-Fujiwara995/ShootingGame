#pragma once
#include "Engine/GameObject.h"
/// <summary>
/// ƒNƒ‰ƒX‚ğì‚é‚Æ‚«‚É•Ö—˜‚È‚Ğ‚ÈŒ`
/// </summary>
class TestScene : public GameObject
{
public:
	TestScene(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};