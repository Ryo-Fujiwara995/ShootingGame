#pragma once
#include "Engine/GameObject.h"
#include <string>

class HpBar : public GameObject
{
private:
	/// <summary>
	/// HP�\�����s�����߂̉摜�n���h��
	/// hHpNumPict_[0] : 100�̈�
	/// hHpNumPict_[1] :  10�̈�
	/// hHpNumPict_[2] :   1�̈�
	/// </summary>
	int hHpNumPict_[3];
	std::string hpStr_; // ��F"005"

	// --- �����`��p�萔 ---
	static constexpr int CHAR_WIDTH = 16;
	static constexpr int CHAR_HEIGHT = 32;
	static constexpr int CHAR_START_CODE = 33; // ASCII�R�[�h�̊J�n�ʒu
public:
	HpBar(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};
