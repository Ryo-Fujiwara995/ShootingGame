#include "HpBar.h"
#include "Engine/Image.h"
HpBar::HpBar(GameObject* parent)
{
}

void HpBar::Initialize()
{
    // プレイヤーの取得
    //player_ = FindObject<Player>("Player");
    //assert(player_ != nullptr);

    // 画像のロード（仮の矩形画像）
    hBackGroundHandle_ = Image::Load("Images\\HpBarFrame.png");
    //hBarHandle_ = Image::Load("UI\\HpBar_Fill.png");

    hpRate_ = 1.0f;
}

void HpBar::Update()
{
}

void HpBar::Draw()
{
	Transform BackGroundTransform;
	BackGroundTransform.scale_ = XMFLOAT3(0.5f, 0.1f, 1.0f);
	BackGroundTransform.position_ = XMFLOAT3(0.0f, 0.0f, -1.0f);
    Image::SetTransform(hBackGroundHandle_, BackGroundTransform);
	Image::Draw(hBackGroundHandle_);
    // HpBarのゲージ追加中
}

void HpBar::Release()
{
}
