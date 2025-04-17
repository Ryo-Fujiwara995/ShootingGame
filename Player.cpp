#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"

Player::Player(GameObject* parent):GameObject(parent,"Player"), 
			hPlayerModel_(-1),hPlayerSwimmingModel_(-1),hPlayerFloatingModel_(-1),
			playerState_(), isRotateRight_(false), originalRotateRight_(0.0f), isRotateLeft_(false),originalRotateLeft_(0.0f)
{
}

void Player::Initialize()
{

	hPlayerModel_ = Model::Load("Models\\Player\\PlayerDefault.fbx");
	assert(hPlayerModel_ >= 0);

	hPlayerSwimmingModel_ = Model::Load("Models\\Player\\PlayerSwimming.fbx");
	Model::SetAnimFrame(hPlayerSwimmingModel_, 0, 136, 1.0);
	assert(hPlayerSwimmingModel_ >= 0);

	hPlayerFloatingModel_ = Model::Load("Models\\Player\\PlayerFloating.fbx");
	Model::SetAnimFrame(hPlayerFloatingModel_, 0, 40, 1.0);
	assert(hPlayerFloatingModel_ >= 0);


}

void Player::Update()
{
	if (!(playerState_ = PLAYER_ID_DEFAULT))
		playerState_ = PLAYER_ID_DEFAULT; // ������Ԃɖ߂�

	// �L�[�{�[�h�ړ� WASD��GAMEPAD�ł����A���X�e�B�b�N�B�ړ��L�[��GAMEPAD�ł����E�X�e�B�b�N�Ɍ����Ă�
	if (Input::IsKey(DIK_W)) {
		playerState_ = PLAYER_ID_FLOAT;
		transform_.position_.y += 0.1f;
		Model::GetAnimFrame(hPlayerFloatingModel_);
	}
	if (Input::IsKey(DIK_S)) {
		playerState_ = PLAYER_ID_FLOAT;
		transform_.position_.y -= 0.1f;
		Model::GetAnimFrame(hPlayerFloatingModel_);
	}
	if (Input::IsKey(DIK_A)) { // ��
		playerState_ = PLAYER_ID_SWIM;
		transform_.position_.x -= 0.1f;
		Model::GetAnimFrame(hPlayerSwimmingModel_);
	}

	if (Input::IsKey(DIK_D)) { // �E
		playerState_ = PLAYER_ID_SWIM;
		transform_.position_.x += 0.1f;
		Model::GetAnimFrame(hPlayerSwimmingModel_);
	}

	// ���E��]
	if (Input::IsKey(DIK_LEFT)) {
		transform_.rotate_.y += 0.05f; // �E��]
	}
	if (Input::IsKey(DIK_RIGHT)) {
		transform_.rotate_.y -= 0.05f; // ����]
	}
	// ------------------------------
	// GAMEPAD�ł̓��͊֘A ���X�e�B�b�N�ňړ��@�E�X�e�B�b�N�ŉ�]
	// ------------------------------

	// ���X�e�B�b�N�̓��͂��擾�ipadID = 0:1P�z��j
	XMFLOAT3 stickL = Input::GetPadStickL(0);

	// �X�e�B�b�N���͂��L���ȂƂ����������i�f�b�h�]�[���΍�j
	if (fabs(stickL.x) > 0.05f || fabs(stickL.y) > 0.05f) {
		const float moveSpeed = 0.2f;

		// �v���C���[�̉�]�iY���j���擾
		float yaw = transform_.rotate_.y;

		// ��]�s����쐬�iY���̂݁j
		XMMATRIX rotMatrix = XMMatrixRotationY(yaw);

		// ���͂���ړ��x�N�g�����쐬�iZ = �O�i�j
		XMVECTOR localMoveVec = XMVectorSet(stickL.x, 0.0f, stickL.y, 0.0f);

		// ��]��K�p���āu���[���h�����̈ړ��x�N�g���v�ɕϊ�
		XMVECTOR worldMoveVec = XMVector3Transform(localMoveVec, rotMatrix);

		// �ړ����x�𔽉f
		worldMoveVec = XMVectorScale(worldMoveVec, moveSpeed);

		// �ʒu�ɉ��Z
		XMVECTOR posVec = XMLoadFloat3(&transform_.position_);
		posVec = XMVectorAdd(posVec, worldMoveVec);
		XMStoreFloat3(&transform_.position_, posVec);
	}

	// �j���@���j���I�Ȃ�
	if (fabs(Input::GetPadStickL(0).x) > 0.05f || fabs(Input::GetPadStickL(0).y) > 0.05f) {
		playerState_ = PLAYER_ID_SWIM;
	}
	// �����@
	if (Input::IsKey(XINPUT_GAMEPAD_RIGHT_SHOULDER)) {
		playerState_ = PLAYER_ID_FLOAT;
		transform_.position_.y += 0.1f;
	}
	// ���ށ@
	if (Input::IsKey(XINPUT_GAMEPAD_LEFT_SHOULDER)) {
		playerState_ = PLAYER_ID_FLOAT;
		transform_.position_.y -= 0.1f;
	}
	// �E�X�e�B�b�N�̓��͂��擾�ipadID = 0:1P�z��j
	XMFLOAT3 stickR = Input::GetPadStickR(0);

	// �X�e�B�b�N�������ł��X���Ă���Ƃ��̂݉�]
	if (fabs(stickR.x) > 0.05f) {
		const float rotateSpeed = 0.05f;
		transform_.rotate_.y += -stickR.x * rotateSpeed;
	}

	// ------------------------------
	// �J�����Ǐ]�i�v���C���[��]�ɉ����Ď��_�𒲐��j
	// ------------------------------
	//XMFLOAT3 offset = XMFLOAT3(0.0f, 3.0f, -8.0f);  // ����{��
	XMFLOAT3 offset = XMFLOAT3(0.0f, 20.0f, -20.0f);  // ����{��

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
	// �����������܂܂��Ƃ��̂܂܂Ȃ̂ŁAif(!(playerState_ = PLAYER_ID_DEFAULT) PLAYER_ID_DEFAULT)�́A�Ȃ�

	switch (playerState_)
	{
	case PLAYER_ID_DEFAULT:		// 0 - 180 fps
		Model::SetTransform(hPlayerModel_, transform_);
		// Model::SetAnimFrame(hPlayerModel_, 0, 180, 1.0f);
		Model::Draw(hPlayerModel_);
		break;

	case PLAYER_ID_SWIM:	// 0 - 136 fps
		Model::SetTransform(hPlayerSwimmingModel_, transform_);
		// Model::SetAnimFrame(hPlayerSwimmingModel_, 0, 136, 1.0f);
		Model::Draw(hPlayerSwimmingModel_);
		break;

	case PLAYER_ID_FLOAT:	// 0 - 40 fps
		Model::SetTransform(hPlayerFloatingModel_, transform_);
		// Model::SetAnimFrame(hPlayerFloatingModel_, 0, 40, 1.0f);
		Model::Draw(hPlayerFloatingModel_);
		break;

	case PLAYER_ID_MAX:
		break;
	}
}

void Player::Release()
{
}
