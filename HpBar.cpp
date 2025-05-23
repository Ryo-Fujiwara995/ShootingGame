#include "HpBar.h"
#include "Engine/Image.h"
#include "Player.h"
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "GameSetting.h"

HpBar::HpBar(GameObject* parent)
	: GameObject(parent, "HpBar")
{
}

void HpBar::Initialize()
{
	for (int i = PLAYER_HP_NUMBER_DIGITS_MIN; i < PLAYER_HP_NUMBER_DIGITS_MAX; i++) {
		hHpNumPict_[i] = Image::Load("char.png"); // �e���������摜��OK
		assert(hHpNumPict_[i] >= INVALID_IMAGE_HANDLE);
	}
	Visible();
}

void HpBar::Update()
{
	Player* pPlayer = dynamic_cast<Player*>(GetParent());
	if (pPlayer) {
		int hp = std::clamp(pPlayer->GetHp(), 0, 999);
		std::ostringstream oss;
		oss << std::setw(3) << std::setfill('0') << hp;
		hpStr_ = oss.str(); // ��F"007"
	}
}

void HpBar::Draw()
{
	for (int i = PLAYER_HP_NUMBER_DIGITS_MIN; i < PLAYER_HP_NUMBER_DIGITS_MAX; ++i) {
		char c = hpStr_[i];
		int index = static_cast<int>(c) - CHAR_START_CODE;

		if (index >= 0 && index < 94) {
			int srcX = (index % 16) * CHAR_WIDTH;
			int srcY = (index / 16) * CHAR_HEIGHT;

			Transform drawTransform = transform_;
			drawTransform.position_.x += i * CHAR_WIDTH;  // �� i�ŉ��ɂ��炷�i16px���j
			drawTransform.position_.y += 0;               // �� �K�v�ɉ�����Y������
			drawTransform.position_.z = 0;

			Image::SetRect(hHpNumPict_[i], srcX, srcY, CHAR_WIDTH, CHAR_HEIGHT);
			Image::SetTransform(hHpNumPict_[i], drawTransform);
			Image::Draw(hHpNumPict_[i]);
			Image::ResetRect(hHpNumPict_[i]);
		}
	}
}

void HpBar::Release()
{
}
