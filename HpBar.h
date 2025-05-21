#pragma once
#include "Engine/GameObject.h"
#include "Player.h"
class HpBar :
    public GameObject
{
private:
	Player* player_ = nullptr;            // 参照先
	int hBackGroundHandle_;      // 背景画像ハンドル（黒や灰色）
	int hBarHandle_;             // ゲージ本体（赤など）
	float hpRate_;              // 表示用のHP割合（0.0～1.0）
public:
	HpBar(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

