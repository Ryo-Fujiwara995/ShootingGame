#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
Player::Player(GameObject* parent):GameObject(parent,"Player"), hPlayerModel_(-1)
{
}

void Player::Initialize()
{
	hPlayerModel_ = Model::Load("Models\\Player\\Player.fbx");
	assert(hPlayerModel_ >= 0);
	//hPlayerSwimmingModel_ = Model::Load("Models\\Player\\PlayerSwimming.fbx");
	//assert(hPlayerSwimmingModel_ >= 0);
}

void Player::Update()
{
	// 移動関連 キーボード + マウス
	// コントローラ
	// 下を押しながら、Lボタンで、潜る 
	if (Input::IsPadButton(XINPUT_GAMEPAD_DPAD_LEFT) && Input::IsPadButton(XINPUT_GAMEPAD_LEFT_SHOULDER)) {
		transform_.position_.y -= 0.1f;
	}
	// 上を押しながら、Rボタンで、上がる
	if (Input::IsPadButton(XINPUT_GAMEPAD_DPAD_RIGHT) && Input::IsPadButton(XINPUT_GAMEPAD_RIGHT_SHOULDER)) {
		transform_.position_.y += 0.1f;
	}
	
	// debug
	if(Input::IsKey(DIK_UP))
		transform_.position_.y += 0.1f;
	if(Input::IsKey(DIK_DOWN))
		transform_.position_.y -= 0.1f;
}

void Player::Draw()
{
	Model::SetTransform(hPlayerModel_, transform_);
	Model::Draw(hPlayerModel_);

	//Model::SetTransform(hPlayerSwimmingModel_, transform_);
	//Model::Draw(hPlayerSwimmingModel_);
	
}

void Player::Release()
{
}
