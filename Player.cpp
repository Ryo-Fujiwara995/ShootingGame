#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "GameSetting.h"
#include "Engine/CsvReader.h"
#include "Engine/Image.h"
#include <algorithm>
Player::Player(GameObject* parent):GameObject(parent,"Player"), 
			hPlayerModel_(-1),hPlayerSwimmingModel_(-1),hPlayerFloatingModel_(-1),playerMoveSpeed_(0.2f),
			playerState_(), cameraYaw_(0.0f),cameraPitch_(0.0f),cameraDistance_(10.0f),
	        initCameraDistance_(10.0f), cameraZoomSpeed_(0.2f),
            isRotateRight_(), originalRotateRight_(), isRotateLeft_(), originalRotateLeft_(),
            cameraMinDistance_(5.0f), cameraMaxDistance_(20.0f), cameraRotateSpeed_(0.05f)
{
}

void Player::Initialize()
{

	hPlayerModel_ = Model::Load("Models\\Player\\PlayerDefault.fbx");
	assert(hPlayerModel_ >= INVALID_MODEL_HANDLE);

	hPlayerSwimmingModel_ = Model::Load("Models\\Player\\PlayerSwimming.fbx");
	//Model::SetAnimFrame(hPlayerSwimmingModel_, 0, 136, 1.0);
	assert(hPlayerSwimmingModel_ >= INVALID_MODEL_HANDLE);

	hPlayerFloatingModel_ = Model::Load("Models\\Player\\PlayerFloating.fbx");
	//Model::SetAnimFrame(hPlayerFloatingModel_, 0, 40, 1.0);
	assert(hPlayerFloatingModel_ >= INVALID_MODEL_HANDLE);

    SphereCollider* playerCollider = new SphereCollider(XMFLOAT3(0, 0, 0), 0.5f);
    AddCollider(playerCollider);

    // Csvファイルの読み込み
    CsvReader playerCsv;
    playerCsv.Load("Csv\\PlayerSetting.csv");
}

void Player::Update()
{
	if (!(playerState_ = PLAYER_ID_DEFAULT))
		playerState_ = PLAYER_ID_DEFAULT; // 初期状態に戻す



    // --- プレイヤー移動（左スティック） ---
    XMFLOAT3 stickL = Input::GetPadStickL();
    if (fabs(stickL.x) > Input::StickDeadZone || fabs(stickL.y) > Input::StickDeadZone) {
        
        XMMATRIX rot = XMMatrixRotationY(cameraYaw_);
        XMVECTOR localMove = XMVectorSet(stickL.x, 0.0f, stickL.y, 0.0f);
        XMVECTOR worldMove = XMVector3Transform(localMove, rot);
        worldMove = XMVectorScale(worldMove, playerMoveSpeed_);
        XMVECTOR pos = XMLoadFloat3(&transform_.position_);
        pos = XMVectorAdd(pos, worldMove);
        XMStoreFloat3(&transform_.position_, pos);
    }

    // --- カメラ制御（右スティック） ---
    XMFLOAT3 stickR = Input::GetPadStickR(Input::PLAYER_ONE_PAD_ID);
    bool isZoomMode = Input::IsPadButton(XINPUT_GAMEPAD_RIGHT_SHOULDER);

    if (isZoomMode) {
        cameraDistance_ -= stickR.y * cameraZoomSpeed_;
        cameraDistance_ = std::clamp(cameraDistance_, 5.0f, 20.0f);// Playerの最小・最大距離
    }
    else {
        cameraYaw_ += stickR.x * 0.05f;
        cameraPitch_ -= stickR.y * 0.05f;
        cameraPitch_ = std::clamp(cameraPitch_, -XM_PIDIV4, XM_PIDIV4);
    }

    // --- カメラ位置計算（回転 + 直線ズーム） ---
    XMMATRIX rotMat = XMMatrixRotationRollPitchYaw(cameraPitch_, cameraYaw_, 0.0f);
    XMVECTOR forward = XMVectorSet(0, 0, 1, 0);
    XMVECTOR direction = XMVector3TransformNormal(forward, rotMat);
    direction = XMVector3Normalize(direction);

    XMVECTOR playerPos = XMLoadFloat3(&transform_.position_);
    XMVECTOR cameraPos = XMVectorSubtract(playerPos, XMVectorScale(direction, cameraDistance_));

    // カメラに高さを加える（常に少し上から見下ろす）
    XMVECTOR heightOffset = XMVectorSet(0, 2.5f, 0, 0);
    cameraPos = XMVectorAdd(cameraPos, heightOffset);

    XMFLOAT3 camPos;
    XMStoreFloat3(&camPos, cameraPos);

    // 注視点をプレイヤーの頭付近に設定
    XMFLOAT3 target = transform_.position_;
    target.y += 1.5f;

    Camera::SetPosition(camPos);
    Camera::SetTarget(target);

	//--- カメラリセット ---
	if (Input::IsPadButtonDown(XINPUT_GAMEPAD_RIGHT_THUMB)) {// Rスティック押し込み
		// カメラ方向と距離をリセット
		cameraYaw_ = 0.0f;
		cameraPitch_ = 0.0f;
		cameraDistance_ = initCameraDistance_;
	}
    //-------------------------
	// keyboard input for player
    //-------------------------
    // --- キーボード移動処理（左右） ---
    if (Input::IsKey(DIK_A) || Input::IsKey(DIK_D))
    {
        // Aキー：-1、Dキー：+1
        float moveDir = 0.0f;
        if (Input::IsKey(DIK_A)) moveDir -= 1.0f;
        if (Input::IsKey(DIK_D)) moveDir += 1.0f;

         //カメラのY軸方向に対して直角方向に移動（左右方向）
        XMMATRIX rot = XMMatrixRotationY(cameraYaw_);
        XMVECTOR rightVec = XMVector3TransformNormal(XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f), rot); // ワールドの右方向

        XMVECTOR moveVec = XMVectorScale(rightVec, moveDir * playerMoveSpeed_);
        XMVECTOR pos = XMLoadFloat3(&transform_.position_);
        pos = XMVectorAdd(pos, moveVec);
        XMStoreFloat3(&transform_.position_, pos);
    }

}

void Player::Draw()
{
	// 初期化したままだとそのままなので、if(!(playerState_ = PLAYER_ID_DEFAULT) PLAYER_ID_DEFAULT)は、なし
	switch (playerState_)
	{
	case PLAYER_ID_DEFAULT:		// 0 - 180 fps -> anim なし？？
		Model::SetTransform(hPlayerModel_, transform_);
		// Model::SetAnimFrame(hPlayerModel_, 0, 180, 1.0f);
		Model::Draw(hPlayerModel_);
		break;

	case PLAYER_ID_SWIM:	// 0 - 136 fps // 0 - 271 fps
		Model::SetTransform(hPlayerSwimmingModel_, transform_);
        Model::SetAnimFrame(hPlayerSwimmingModel_, 0, 136, 1.0f);
		Model::Draw(hPlayerSwimmingModel_);
		break;

	case PLAYER_ID_FLOAT:	// 0 - 40 fps
		Model::SetTransform(hPlayerFloatingModel_, transform_);
		// Model::SetAnimFrame(hPlayerFloatingModel_, 0, 40, 1.0f);
	    Model::Draw(hPlayerFloatingModel_);

	case PLAYER_ID_MAX:
		break;
	}
    
}

void Player::Release()
{
}

void Player::OnCollision(GameObject* pTarget)
{
	if (pTarget->GetObjectName() == "SpiralEnemy")
	{
		//hp_ -= 1;
		//if (hp_ <= 0)
		//{
		//	//KillMe();
		//}
        KillMe();
	}

    if (pTarget->GetObjectName() == "StraightLineEnemy")
    {
        //hp_ -= 1;
        //if (hp_ <= 0)
        //{
        //    //KillMe();
        //}
        KillMe();
    }
}
