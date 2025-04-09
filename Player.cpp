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
	// �ړ��֘A �L�[�{�[�h + �}�E�X
	// �R���g���[��
	// ���������Ȃ���AL�{�^���ŁA���� 
	if (Input::IsPadButton(XINPUT_GAMEPAD_DPAD_LEFT) && Input::IsPadButton(XINPUT_GAMEPAD_LEFT_SHOULDER)) {
		transform_.position_.y -= 0.1f;
	}
	// ��������Ȃ���AR�{�^���ŁA�オ��
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
