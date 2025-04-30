#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "GameSetting.h"
#include <algorithm>
Player::Player(GameObject* parent):GameObject(parent,"Player"), 
			hPlayerModel_(-1),hPlayerSwimmingModel_(-1),hPlayerFloatingModel_(-1),
			playerState_(), cameraYaw_(0.0f),cameraPitch_(0.0f),cameraDistance_(10.0f)
{
}

void Player::Initialize()
{

	hPlayerModel_ = Model::Load("Models\\Player\\PlayerDefault.fbx");
	assert(hPlayerModel_ >= 0);

	hPlayerSwimmingModel_ = Model::Load("Models\\Player\\PlayerSwimming.fbx");
	//Model::SetAnimFrame(hPlayerSwimmingModel_, 0, 136, 1.0);
	assert(hPlayerSwimmingModel_ >= 0);

	hPlayerFloatingModel_ = Model::Load("Models\\Player\\PlayerFloating.fbx");
	//Model::SetAnimFrame(hPlayerFloatingModel_, 0, 40, 1.0);
	assert(hPlayerFloatingModel_ >= 0);


}

void Player::Update()
{
	if (!(playerState_ = PLAYER_ID_DEFAULT))
		playerState_ = PLAYER_ID_DEFAULT; // ������Ԃɖ߂�

    // --- �v���C���[�ړ��i���X�e�B�b�N�j ---
    XMFLOAT3 stickL = Input::GetPadStickL(0);
    if (fabs(stickL.x) > 0.05f || fabs(stickL.y) > 0.05f) {
        const float moveSpeed = 0.2f;
        XMMATRIX rot = XMMatrixRotationY(cameraYaw_);
        XMVECTOR localMove = XMVectorSet(stickL.x, 0.0f, stickL.y, 0.0f);
        XMVECTOR worldMove = XMVector3Transform(localMove, rot);
        worldMove = XMVectorScale(worldMove, moveSpeed);
        XMVECTOR pos = XMLoadFloat3(&transform_.position_);
        pos = XMVectorAdd(pos, worldMove);
        XMStoreFloat3(&transform_.position_, pos);
    }

    // --- �J��������i�E�X�e�B�b�N�j ---
    XMFLOAT3 stickR = Input::GetPadStickR(0);
    bool isZoomMode = Input::IsPadButton(XINPUT_GAMEPAD_RIGHT_SHOULDER);

    if (isZoomMode) {
        cameraDistance_ -= stickR.y * 0.2f;
        cameraDistance_ = std::clamp(cameraDistance_, 5.0f, 20.0f);// Player�̍ŏ��E�ő勗��
    }
    else {
        cameraYaw_ += stickR.x * 0.05f;
        cameraPitch_ -= stickR.y * 0.05f;
        cameraPitch_ = std::clamp(cameraPitch_, -XM_PIDIV4, XM_PIDIV4);
    }

    // --- �J�����ʒu�v�Z�i��] + �����Y�[���j ---
    XMMATRIX rotMat = XMMatrixRotationRollPitchYaw(cameraPitch_, cameraYaw_, 0.0f);
    XMVECTOR forward = XMVectorSet(0, 0, 1, 0);
    XMVECTOR direction = XMVector3TransformNormal(forward, rotMat);
    direction = XMVector3Normalize(direction);

    XMVECTOR playerPos = XMLoadFloat3(&transform_.position_);
    XMVECTOR cameraPos = XMVectorSubtract(playerPos, XMVectorScale(direction, cameraDistance_));

    // �J�����ɍ�����������i��F��ɏ����ォ�猩���낷�j
    XMVECTOR heightOffset = XMVectorSet(0, 2.5f, 0, 0);
    cameraPos = XMVectorAdd(cameraPos, heightOffset);

    XMFLOAT3 camPos;
    XMStoreFloat3(&camPos, cameraPos);

    // �����_���v���C���[�̓��t�߂ɐݒ�i���R�Ɂj
    XMFLOAT3 target = transform_.position_;
    target.y += 1.5f;

    Camera::SetPosition(camPos);
    Camera::SetTarget(target);
   // IsPadZRDown

	//--- �J�������Z�b�g ---
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_RIGHT_THUMB)) {// R�X�e�B�b�N��������
		// �J���������Ƌ��������Z�b�g
		cameraYaw_ = 0.0f;
		cameraPitch_ = 0.0f;
		cameraDistance_ = initCameraDistance_;
	}
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

	case PLAYER_ID_MAX:
		break;
    default:
        break;
	}
}

void Player::Release()
{
}
