#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"

Player::Player(GameObject* parent):GameObject(parent,"Player"), 
			hPlayerModel_(-1),hPlayerSwimmingModel_(-1),hPlayerFloatingModel_(-1),
			playerState_(PLAYER_ID_DEFAULT)
{
}

void Player::Initialize()
{

	hPlayerModel_ = Model::Load("Models\\Player\\PlayerDefault.fbx");
	assert(hPlayerModel_ >= 0);
	hPlayerSwimmingModel_ = Model::Load("Models\\Player\\PlayerSwimming.fbx");
	assert(hPlayerSwimmingModel_ >= 0);
	hPlayerFloatingModel_ = Model::Load("Models\\Player\\PlayerFloating.fbx");
	assert(hPlayerFloatingModel_ >= 0);
}

void Player::Update()
{
	if (!(playerState_ = PLAYER_ID_DEFAULT))
		playerState_ = PLAYER_ID_DEFAULT; // ������Ԃɖ߂�

	// �L�[�{�[�h�ړ� WASD��GAMEPAD�ł����A���X�e�B�b�N�B�ړ��L�[��GAMEPAD�ł����E�X�e�B�b�N�Ɍ����Ă�
	if (Input::IsKey(DIK_W)) {

		transform_.position_.y += 0.1f;
		playerState_ = PLAYER_ID_FLOAT;// Model::SetAnimFrame(hPlayerFloatingModel_, 0, 40, 1.0f);
	}
	if (Input::IsKey(DIK_S)) {

		transform_.position_.y -= 0.1f;
		playerState_ = PLAYER_ID_FLOAT; //Model::SetAnimFrame(hPlayerFloatingModel_, 0, 40, 1.0f);
	}
	if (Input::IsKey(DIK_A)) {

		transform_.position_.x -= 0.1f;
		
		playerState_ = PLAYER_ID_SWIM;// Model::SetAnimFrame(hPlayerSwimmingModel_, 0, 136, 1.0f);
	}
	if (Input::IsKey(DIK_D)) {

		transform_.position_.x += 0.1f;
		playerState_ = PLAYER_ID_SWIM; //Model::SetAnimFrame(hPlayerSwimmingModel_, 0, 136, 1.0f);
	}
	// ���E��]
	if (Input::IsKey(DIK_LEFT)) {
		transform_.rotate_.y += 0.05f; // �E��]
	}
	if (Input::IsKey(DIK_RIGHT)) {
		transform_.rotate_.y -= 0.05f; // ����]
	}

	// ------------------------------
	// �J�����Ǐ]�i�v���C���[��]�ɉ����Ď��_�𒲐��j
	// ------------------------------
	XMFLOAT3 offset = XMFLOAT3(0.0f, 3.0f, -8.0f);  // ����{��

	float yaw = transform_.rotate_.y;
	XMMATRIX rotMatrix = XMMatrixRotationY(yaw);

	XMVECTOR offsetVec = XMVectorSet(offset.x, offset.y, offset.z, 0.0f);
	XMVECTOR rotatedOffset = XMVector3Transform(offsetVec, rotMatrix);

	XMVECTOR playerPosVec = XMLoadFloat3(&transform_.position_);
	XMVECTOR camPosVec = XMVectorAdd(playerPosVec, rotatedOffset);

	XMFLOAT3 camPos;
	XMStoreFloat3(&camPos, camPosVec);

	Camera::SetPosition(camPos);                    // ���_
	Camera::SetTarget(transform_.position_);        // �œ_�i�v���C���[�j
	Camera::Update();                               // �s��X�V


}

void Player::Draw()
{
	switch (playerState_)
	{
	case PLAYER_ID_DEFAULT:		// 0 - 180 fps
		Model::SetAnimFrame(hPlayerModel_, 0, 180, 1.0f);
		Model::SetTransform(hPlayerModel_, transform_);
		Model::Draw(hPlayerModel_);

		break;

	case PLAYER_ID_SWIM:	// 0 - 136 fps
		Model::SetAnimFrame(hPlayerSwimmingModel_, 0, 136, 1.0f);
		Model::SetTransform(hPlayerSwimmingModel_, transform_);
		Model::Draw(hPlayerSwimmingModel_);

		break;

	case PLAYER_ID_FLOAT:	// 0 - 40 fps
		Model::SetAnimFrame(hPlayerFloatingModel_, 0, 40, 1.0f);
		Model::SetTransform(hPlayerFloatingModel_, transform_);
		Model::Draw(hPlayerFloatingModel_);

		break;
	}
}

void Player::Release()
{
}
