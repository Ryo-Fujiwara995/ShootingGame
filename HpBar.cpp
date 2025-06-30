#include "HpBar.h"
#include "Engine/Image.h"
#include "Player.h"
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "GameSetting.h"
#include "Engine/Camera.h"

HpBar::HpBar(GameObject* parent)
	: GameObject(parent, "HpBar")
{
}

void HpBar::Initialize()
{
	for (int i = PLAYER_HP_NUMBER_DIGITS_MIN_ARRAY; i < PLAYER_HP_NUMBER_DIGITS_MAX_ARRAY; i++) {
		hHpNumPict_[i] = Image::Load("char.png"); // �e���������摜��OK
		assert(hHpNumPict_[i] >= INVALID_IMAGE_HANDLE);
		
	}
	Visible();
}

void HpBar::Update()
{
	Player* pPlayer = dynamic_cast<Player*>(GetParent());
	if (pPlayer) {	// ���݂́A1���\��
		int hp = std::clamp(pPlayer->GetHp(), PLAYER_HP_MIN, PLAYER_HP_MAX);
		std::ostringstream oss;
		oss << std::setw(PLAYER_HP_NUMBER_DIGITS_MIN) << std::setfill('0') << hp; // ����0����
		hpStr_ = oss.str();
	}

}

void HpBar::Draw()
{
	for (int i = PLAYER_HP_NUMBER_DIGITS_MIN_ARRAY; i < PLAYER_HP_NUMBER_DIGITS_MAX_ARRAY; i++) {
		char c = hpStr_[i];
		int index = static_cast<int>(c) - CHAR_START_CODE;

		if (index >= CHAR_MIN_INDEX && index < CHAR_TOTAL_COUNT) {
			int srcX = (index % CHAR_PER_ROW) * CHAR_WIDTH;
			int srcY = (index / CHAR_PER_ROW) * CHAR_HEIGHT;

			Transform drawTransform = transform_; // �� ��ʒu���R�s�[
			drawTransform.position_.x += i * CHAR_WIDTH; // �� �����Ƃ�16px���炷	

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
