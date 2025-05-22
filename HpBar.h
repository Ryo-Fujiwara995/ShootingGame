#pragma once
#include "Engine/GameObject.h"
#include <string>

class HpBar : public GameObject
{
private:
	int hHpNumPict_;
	std::string hpStr_; // 例："005"

	// --- 文字描画用定数 ---
	static constexpr int CHAR_WIDTH = 16;
	static constexpr int CHAR_HEIGHT = 32;
	static constexpr int CHAR_START_CODE = 33; // ASCIIコードの開始位置
public:
	HpBar(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};
