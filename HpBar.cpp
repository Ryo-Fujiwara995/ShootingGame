#include "HpBar.h"
#include "Engine/Image.h"
#include "Player.h"
#include "GameSetting.h"
#include <sstream>
#include <iomanip>
#include <algorithm>


HpBar::HpBar(GameObject* parent)
	: GameObject(parent, "HpBar")
{
}

void HpBar::Initialize()
{
	hHpNumPict_ = Image::Load("char.png");
	assert(hHpNumPict_ >= INVALID_IMAGE_HANDLE);
	Visible(); // Å© ï`âÊãñâ¬ÅI
}

void HpBar::Update()
{
	Player* pPlayer = dynamic_cast<Player*>(GetParent());
	if (pPlayer) {
		int hp = std::clamp(pPlayer->GetHp(), 0, 999);
		std::ostringstream oss;
		oss << std::setw(3) << std::setfill('0') << hp;
		hpStr_ = oss.str();
	}
}

void HpBar::Draw()
{
	for (size_t i = 0; i < hpStr_.size(); ++i) {
		char c = hpStr_[i];
		int index = static_cast<int>(c) - CHAR_START_CODE;

		if (index >= 0 && index < 94) {
			int srcX = (index % 16) * CHAR_WIDTH;
			int srcY = (index / 16) * CHAR_HEIGHT;

			Transform drawTransform;
			drawTransform.position_.x = 100 + i * CHAR_WIDTH;
			drawTransform.position_.y = 100;
			drawTransform.position_.z = 0;

			Image::SetRect(hHpNumPict_, srcX, srcY, CHAR_WIDTH, CHAR_HEIGHT);
			Image::SetTransform(hHpNumPict_, drawTransform);
			Image::Draw(hHpNumPict_);
			Image::ResetRect(hHpNumPict_);
		}
	}
}

void HpBar::Release()
{
}
