#include "Player.h"
#include "SpaceShuttle.h"
#include "HpBar.h"
#include "Engine/Model.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "GameSetting.h"
#include "Engine/Time.h"
#include "Engine/SceneManager.h"
#include "Engine/Audio.h"
#include <algorithm>

Player::Player(GameObject* parent):GameObject(parent,"Player"), 
			hPlayerModel_(INVALID_OBJECT_HANDLE),hPlayerSwimmingModel_(INVALID_OBJECT_HANDLE),hPlayerFloatingModel_(INVALID_OBJECT_HANDLE),playerMoveSpeed_(0.2f),
            hp_(5), cameraYaw_(0.0f),cameraPitch_(0.0f),cameraDistance_(10.0f),
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

	hDamagePict_ = Image::Load("Images\\PlayScene\\Damage.png");
    assert(hDamagePict_ >= INVALID_IMAGE_HANDLE);

    SphereCollider* playerCollider = new SphereCollider(XMFLOAT3(0, 0, 0), 0.5f);//中心と半径
    AddCollider(playerCollider);

    HpBar* hpBar = new HpBar(this);
    hpBar->Initialize();
    PushBackChild(hpBar); // 子として登録
}

void Player::Update()
{
    //移動関係
    {   
        //-------------------------
        // controller input
        //-------------------------
        // --- プレイヤー移動（左スティック） ---
        XMFLOAT3 stick = Input::GetPadStickL(); // 左スティック入力（x:左右, y:前後）

        // 入力が有効なときだけ処理
        if (fabs(stick.x) > Input::StickDeadZone || fabs(stick.y) > Input::StickDeadZone) {

            // --- 移動処理 ---
            const float moveSpeed = 0.1f;
            XMVECTOR moveVec = XMVectorSet(stick.x, 0, stick.y, 0);
            moveVec = XMVector3Normalize(moveVec); // 斜めを正規化
            moveVec = XMVectorScale(moveVec, moveSpeed);

            XMVECTOR pos = XMLoadFloat3(&transform_.position_);
            pos = XMVectorAdd(pos, moveVec);
            XMStoreFloat3(&transform_.position_, pos);

            // --- 向き（Y軸）をスティック方向に合わせて旋回 ---
            XMFLOAT3 moveDir;
            XMStoreFloat3(&moveDir, moveVec);

            float targetAngle = atan2f(moveDir.x, moveDir.z); // Z前提で前向き
            float currentAngle = XMConvertToRadians(transform_.rotate_.y);

            // 差分を [-π, π] に補正
            float delta = targetAngle - currentAngle;
            while (delta > XM_PI)  delta -= XM_2PI;
            while (delta < -XM_PI) delta += XM_2PI;

            // 旋回速度を制限（1フレームで最大5度回転）
            const float rotateSpeed = XMConvertToRadians(5.0f); // ≒5度
            delta = std::clamp(delta, -rotateSpeed, rotateSpeed);
            currentAngle += delta;

            // Y軸回転更新
            transform_.rotate_.y = XMConvertToDegrees(currentAngle);
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
        XMMATRIX rotMat = XMMatrixRotationRollPitchYaw(cameraPitch_, cameraYaw_, 0);
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
        // keyboard input
        //-------------------------
        XMVECTOR moveVec = XMVectorZero();

        // キーボード入力から移動ベクトル作成（Z軸前提）
        if (Input::IsKey(DIK_W)) moveVec = XMVectorAdd(moveVec, XMVectorSet(0, 0,  1, 0));
        if (Input::IsKey(DIK_S)) moveVec = XMVectorAdd(moveVec, XMVectorSet(0, 0, -1, 0));
        if (Input::IsKey(DIK_A)) moveVec = XMVectorAdd(moveVec, XMVectorSet(-1, 0, 0, 0));
        if (Input::IsKey(DIK_D)) moveVec = XMVectorAdd(moveVec, XMVectorSet( 1, 0, 0, 0));

        // 移動ベクトルの長さが0でなければ処理
        if (!XMVector3Equal(moveVec, XMVectorZero()))
        {
            // --- 移動 ---
            moveVec = XMVector3Normalize(moveVec);
            const float moveSpeed = 0.1f;
            XMVECTOR pos = XMLoadFloat3(&transform_.position_);
            pos = XMVectorAdd(pos, XMVectorScale(moveVec, moveSpeed));
            XMStoreFloat3(&transform_.position_, pos);

            // --- 旋回 ---
            XMFLOAT3 moveDir;
            XMStoreFloat3(&moveDir, moveVec);
            float targetAngle = atan2f(moveDir.x, moveDir.z); // Z前提
            float currentAngle = XMConvertToRadians(transform_.rotate_.y);

            float delta = targetAngle - currentAngle;
            while (delta > XM_PI)  delta -= XM_2PI;
            while (delta < -XM_PI) delta += XM_2PI;

            const float rotateSpeed = XMConvertToRadians(5.0f); // 5度/フレーム
            delta = std::clamp(delta, -rotateSpeed, rotateSpeed);
            currentAngle += delta;

            transform_.rotate_.y = XMConvertToDegrees(currentAngle);
        }
        //矢印キーによるカメラ操作
        const float cameraRotateSpeed = XMConvertToRadians(2.0f); // 2度/フレーム

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

        //カメラのリセット
        if (Input::IsKeyDown(DIK_Z) || Input::IsPadButtonDown(XINPUT_GAMEPAD_RIGHT_THUMB)) {
            cameraYaw_ = initCameraYaw_;
            cameraPitch_ = initCameraPitch_;
            cameraDistance_ = initCameraDistance_;
        }

    }
    //無敵関係
    if (invincibleTimer_ > PLAYER_INIT_INVINCIBLE_TIMER_MIN) {
        invincibleTimer_ -= Time::GetDeltaTime();
        if (invincibleTimer_ < PLAYER_INIT_INVINCIBLE_TIMER_MIN) {
            invincibleTimer_ = PLAYER_INIT_INVINCIBLE_TIMER_MIN;
        }
    }

	//ダメージフラッシュ関係
    if (isDamageFlashing_) {
        damageFlashTimer_ += Time::GetDeltaTime();
        if (damageFlashTimer_ >= damageFlashDuration_) {
            isDamageFlashing_ = false;
        }
    }
}

void Player::Draw()
{    
    Model::SetTransform(hPlayerModel_, transform_);
	Model::Draw(hPlayerModel_);

    if (isDamageFlashing_) {
        float alpha = 1 - (damageFlashTimer_ / damageFlashDuration_);
        int alphaValue = static_cast<int>(alpha * 255.0f);

        //Transform fullscreen;
        //fullscreen.position_ = { ZERO, ZERO, ZERO };

        Image::SetTransform(hDamagePict_, transform_);
        Image::SetAlpha(hDamagePict_, alpha);
        Image::Draw(hDamagePict_);
    }


}

void Player::Release()
{
}

void Player::OnCollision(GameObject* pTarget)
{
    if ((pTarget->GetObjectName() == "SpiralEnemy") || (pTarget->GetObjectName() == "StraightLineEnemy"))
    {
        // 無敵中はダメージを受けない
        if (invincibleTimer_ > PLAYER_INIT_INVINCIBLE_TIMER_MIN) {
            return;
        }

        // ダメージ処理
        if (hp_ > PLAYER_HP_MIN) {
            hp_ -= PLAYER_HP_DOWN;
             // 赤点滅のダメージフラグを立てる
            isDamageFlashing_ = true;
            damageFlashTimer_ = 0.0f;
            // 無敵タイマーを開始
            invincibleTimer_ = invincibleTime_;
        }

        if (hp_ <= PLAYER_HP_MIN) {// HP が0になったら、Playerを削除してGameOverSceneに移動
            

            KillMe();
            SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
            pSceneManager->ChangeScene(SCENE_ID_GAMEOVER);
        }
    }
}
