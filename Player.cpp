#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"

Player::Player(GameObject* parent):GameObject(parent,"Player"), hPlayerModel_(-1),hPlayerSwimmingModel_(-1),hPlayerFloatingModel_(-1)
{
}

void Player::Initialize()
{
	hPlayerModel_ = Model::Load("Models\\Player\\Player.fbx");
	assert(hPlayerModel_ >= 0);
	hPlayerSwimmingModel_ = Model::Load("Models\\Player\\PlayerSwimming.fbx");
	assert(hPlayerSwimmingModel_ >= 0);
	hPlayerFloatingModel_ = Model::Load("Models\\Player\\PlayerFloating.fbx");
	assert(hPlayerFloatingModel_ >= 0);
}

void Player::Update()
{
	// �J�������v���C���[�ɒǏ]������
	XMFLOAT3 offset = XMFLOAT3(0.0f, 3.0f, -8.0f);
	XMFLOAT3 cameraPos = {
		transform_.position_.x + offset.x,
		transform_.position_.y + offset.y,
		transform_.position_.z + offset.z
	};

	Camera::SetPosition(cameraPos);			 // ���_
	Camera::SetTarget(transform_.position_); // �œ_
	Camera::Update();						 // �s��X�V

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
	//if (PLAYER_ID_STANDBY) {
		Model::SetTransform(hPlayerModel_, transform_);
		Model::Draw(hPlayerModel_);
	//}



	// 0 - 136 fps
	//Model::SetTransform(hPlayerSwimmingModel_, transform_);
	//Model::Draw(hPlayerSwimmingModel_);

	// 0 - 40 fps
	//Model::SetTransform(hPlayerFloatingModel_, transform_);
	//Model::Draw(hPlayerFloatingModel_);
	
}

void Player::Release()
{
}
