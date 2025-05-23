#pragma once
#include "Engine/GameObject.h"
#include <string>

class HpBar : public GameObject
{
private:
	/// <summary>
	/// HP表示を行うための画像ハンドル
	/// hHpNumPict_[0] : 100の位
	/// hHpNumPict_[1] :  10の位
	/// hHpNumPict_[2] :   1の位
	/// </summary>
	int hHpNumPict_[3];
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
