#include "Player.h"
#include "SpaceShuttle.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "GameSetting.h"
#include "Engine/CsvReader.h"
#include "Engine/Image.h"
#include "Engine/Time.h"
#include <algorithm>
Player::Player(GameObject* parent):GameObject(parent,"Player"), 
			hPlayerModel_(-1),hPlayerSwimmingModel_(-1),hPlayerFloatingModel_(-1),playerMoveSpeed_(0.2f),hp_(10),
			playerState_(), cameraYaw_(0.0f),cameraPitch_(0.0f),cameraDistance_(10.0f),
	        initCameraDistance_(10.0f), cameraZoomSpeed_(0.2f),
            isRotateRight_(), originalRotateRight_(), isRotateLeft_(), originalRotateLeft_(),
            cameraMinDistance_(5.0f), cameraMaxDistance_(20.0f), cameraRotateSpeed_(0.05f)
{
    

}

void Player::Initialize()
{
    Instantiate<SpaceShuttle>(this);
	hPlayerModel_ = Model::Load("Models\\Player\\PlayerSitting.fbx");
	assert(hPlayerModel_ >= INVALID_MODEL_HANDLE);

    SphereCollider* playerCollider = new SphereCollider(XMFLOAT3(0, 0, 0), 0.5f);
    AddCollider(playerCollider);

    // Csv�t�@�C���̓ǂݍ���
    CsvReader playerCsv;
    playerCsv.Load("Csv\\PlayerSetting.csv");
}

void Player::Update()
{
    //-------------------------
    // controller input
    //-------------------------
    // --- �v���C���[�ړ��i���X�e�B�b�N�j ---
    XMFLOAT3 stick = Input::GetPadStickL(); // ���X�e�B�b�N���́ix:���E, y:�O��j

    // ���͂��L���ȂƂ���������
    if (fabs(stick.x) > Input::StickDeadZone || fabs(stick.y) > Input::StickDeadZone) {

        // --- �ړ����� ---
        const float moveSpeed = 0.1f;
        XMVECTOR moveVec = XMVectorSet(stick.x, 0.0f, stick.y, 0.0f);
        moveVec = XMVector3Normalize(moveVec); // �΂߂𐳋K��
        moveVec = XMVectorScale(moveVec, moveSpeed);

        XMVECTOR pos = XMLoadFloat3(&transform_.position_);
        pos = XMVectorAdd(pos, moveVec);
        XMStoreFloat3(&transform_.position_, pos);

        // --- �����iY���j���X�e�B�b�N�����ɍ��킹�Đ��� ---
        XMFLOAT3 moveDir;
        XMStoreFloat3(&moveDir, moveVec);

        float targetAngle = atan2f(moveDir.x, moveDir.z); // Z�O��őO����
        float currentAngle = XMConvertToRadians(transform_.rotate_.y);

        // ������ [-��, ��] �ɕ␳
        float delta = targetAngle - currentAngle;
        while (delta > XM_PI)  delta -= XM_2PI;
        while (delta < -XM_PI) delta += XM_2PI;

        // ���񑬓x�𐧌��i1�t���[���ōő�5�x��]�j
        const float rotateSpeed = XMConvertToRadians(5.0f); // ��5�x
        delta = std::clamp(delta, -rotateSpeed, rotateSpeed);
        currentAngle += delta;

        // Y����]�X�V
        transform_.rotate_.y = XMConvertToDegrees(currentAngle);
    }


    // --- �J��������i�E�X�e�B�b�N�j ---
    XMFLOAT3 stickR = Input::GetPadStickR(Input::PLAYER_ONE_PAD_ID);
    bool isZoomMode = Input::IsPadButton(XINPUT_GAMEPAD_RIGHT_SHOULDER);

    if (isZoomMode) {
        cameraDistance_ -= stickR.y * cameraZoomSpeed_;
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

    // �J�����ɍ�����������i��ɏ����ォ�猩���낷�j
    XMVECTOR heightOffset = XMVectorSet(0, 2.5f, 0, 0);
    cameraPos = XMVectorAdd(cameraPos, heightOffset);

    XMFLOAT3 camPos;
    XMStoreFloat3(&camPos, cameraPos);

    // �����_���v���C���[�̓��t�߂ɐݒ�
    XMFLOAT3 target = transform_.position_;
    target.y += 1.5f;

    Camera::SetPosition(camPos);
    Camera::SetTarget(target);

	//--- �J�������Z�b�g ---
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_RIGHT_THUMB)) {// R�X�e�B�b�N��������
		// �J���������Ƌ��������Z�b�g
		cameraYaw_ = 0.0f;
		cameraPitch_ = 0.0f;
		cameraDistance_ = initCameraDistance_;
	}
    //-------------------------
	// keyboard input
    //-------------------------
    XMVECTOR moveVec = XMVectorZero();

    // �L�[�{�[�h���͂���ړ��x�N�g���쐬�iZ���O��j
    if (Input::IsKey(DIK_W)) moveVec = XMVectorAdd(moveVec, XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f));
    if (Input::IsKey(DIK_S)) moveVec = XMVectorAdd(moveVec, XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f));
    if (Input::IsKey(DIK_A)) moveVec = XMVectorAdd(moveVec, XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f));
    if (Input::IsKey(DIK_D)) moveVec = XMVectorAdd(moveVec, XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f));

    // �ړ��x�N�g���̒�����0�łȂ���Ώ���
    if (!XMVector3Equal(moveVec, XMVectorZero()))
    {
        // --- �ړ� ---
        moveVec = XMVector3Normalize(moveVec);
        const float moveSpeed = 0.1f;
        XMVECTOR pos = XMLoadFloat3(&transform_.position_);
        pos = XMVectorAdd(pos, XMVectorScale(moveVec, moveSpeed));
        XMStoreFloat3(&transform_.position_, pos);

        // --- ���� ---
        XMFLOAT3 moveDir;
        XMStoreFloat3(&moveDir, moveVec);
        float targetAngle = atan2f(moveDir.x, moveDir.z); // Z�O��
        float currentAngle = XMConvertToRadians(transform_.rotate_.y);

        float delta = targetAngle - currentAngle;
        while (delta > XM_PI)  delta -= XM_2PI;
        while (delta < -XM_PI) delta += XM_2PI;

        const float rotateSpeed = XMConvertToRadians(5.0f); // 5�x/�t���[��
        delta = std::clamp(delta, -rotateSpeed, rotateSpeed);
        currentAngle += delta;

        transform_.rotate_.y = XMConvertToDegrees(currentAngle);
    }
    //���L�[�ɂ��J��������
    const float cameraRotateSpeed = XMConvertToRadians(1.5f); // 1.5�x/�t���[��

    if (Input::IsKey(DIK_LEFT)) {
        cameraYaw_ -= cameraRotateSpeed;
    }
    if (Input::IsKey(DIK_RIGHT)) {
        cameraYaw_ += cameraRotateSpeed;
    }
    if (Input::IsKey(DIK_UP)) {
        cameraPitch_ -= cameraRotateSpeed;
    }
    if (Input::IsKey(DIK_DOWN)) {
        cameraPitch_ += cameraRotateSpeed;
    }

}

void Player::Draw()
{
	Model::SetTransform(hPlayerModel_, transform_);
	Model::Draw(hPlayerModel_);
}

void Player::Release()
{
}

void Player::OnCollision(GameObject* pTarget)
{
	if ((pTarget->GetObjectName() == "SpiralEnemy") || (pTarget->GetObjectName() == "StraightLineEnemy"))
	{
        if (hp_ > 0) {
            hp_ -= 1;
        }

        if (hp_ <= 0) {
            KillMe();
        }
	}
}
