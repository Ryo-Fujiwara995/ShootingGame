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
		playerState_ = PLAYER_ID_DEFAULT; // 初期状態に戻す

	// キーボード移動 WASDをGAMEPADでいう、左スティック。移動キーをGAMEPADでいう右スティックに見立てる
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
	if (Input::IsKey(DIK_A)) { // 左
		playerState_ = PLAYER_ID_SWIM;
		transform_.position_.x -= 0.1f;
		Model::GetAnimFrame(hPlayerSwimmingModel_);
	}

	if (Input::IsKey(DIK_D)) { // 右
		playerState_ = PLAYER_ID_SWIM;
		transform_.position_.x += 0.1f;
		Model::GetAnimFrame(hPlayerSwimmingModel_);
	}

	// 左右回転
	if (Input::IsKey(DIK_LEFT)) {
		transform_.rotate_.y += 0.05f; // 右回転
	}
	if (Input::IsKey(DIK_RIGHT)) {
		transform_.rotate_.y -= 0.05f; // 左回転
	}
	// ------------------------------
	// GAMEPADでの入力関連 左スティックで移動　右スティックで回転
	// ------------------------------

	// 左スティックの入力を取得（padID = 0:1P想定）
	XMFLOAT3 stickL = Input::GetPadStickL(0);

	// スティック入力が有効なときだけ処理（デッドゾーン対策）
	if (fabs(stickL.x) > 0.05f || fabs(stickL.y) > 0.05f) {
		const float moveSpeed = 0.2f;

		// プレイヤーの回転（Y軸）を取得
		float yaw = transform_.rotate_.y;

		// 回転行列を作成（Y軸のみ）
		XMMATRIX rotMatrix = XMMatrixRotationY(yaw);

		// 入力から移動ベクトルを作成（Z = 前進）
		XMVECTOR localMoveVec = XMVectorSet(stickL.x, 0.0f, stickL.y, 0.0f);

		// 回転を適用して「ワールド方向の移動ベクトル」に変換
		XMVECTOR worldMoveVec = XMVector3Transform(localMoveVec, rotMatrix);

		// 移動速度を反映
		worldMoveVec = XMVectorScale(worldMoveVec, moveSpeed);

		// 位置に加算
		XMVECTOR posVec = XMLoadFloat3(&transform_.position_);
		posVec = XMVectorAdd(posVec, worldMoveVec);
		XMStoreFloat3(&transform_.position_, posVec);
	}

	// 泳ぐ　平泳ぎ的なの
	if (fabs(Input::GetPadStickL(0).x) > 0.05f || fabs(Input::GetPadStickL(0).y) > 0.05f) {
		playerState_ = PLAYER_ID_SWIM;
	}
	// 浮く　
	if (Input::IsKey(XINPUT_GAMEPAD_RIGHT_SHOULDER)) {
		playerState_ = PLAYER_ID_FLOAT;
		transform_.position_.y += 0.1f;
	}
	// 沈む　
	if (Input::IsKey(XINPUT_GAMEPAD_LEFT_SHOULDER)) {
		playerState_ = PLAYER_ID_FLOAT;
		transform_.position_.y -= 0.1f;
	}
	// 右スティックの入力を取得（padID = 0:1P想定）
	XMFLOAT3 stickR = Input::GetPadStickR(0);

	// スティックが少しでも傾いているときのみ回転
	if (fabs(stickR.x) > 0.05f) {
		const float rotateSpeed = 0.05f;
		transform_.rotate_.y += -stickR.x * rotateSpeed;
	}

	// ------------------------------
	// カメラ追従（プレイヤー回転に応じて視点を調整）
	// ------------------------------
	//XMFLOAT3 offset = XMFLOAT3(0.0f, 3.0f, -8.0f);  // 後方＋上
	XMFLOAT3 offset = XMFLOAT3(0.0f, 20.0f, -20.0f);  // 後方＋上

	float yaw = transform_.rotate_.y;
	XMMATRIX rotMatrix = XMMatrixRotationY(yaw);

	XMVECTOR offsetVec = XMVectorSet(offset.x, offset.y, offset.z, 0.0f);

	XMVECTOR rotatedOffset = XMVector3Transform(offsetVec, rotMatrix);

	XMVECTOR playerPosVec = XMLoadFloat3(&transform_.position_);
	XMVECTOR camPosVec = XMVectorAdd(playerPosVec, rotatedOffset);

	XMFLOAT3 camPos;
	XMStoreFloat3(&camPos, camPosVec);

	Camera::SetPosition(camPos);                    // 視点
	Camera::SetTarget(transform_.position_);        // 焦点（プレイヤー）
	Camera::Update();                               // 行列更新

}

void Player::Draw()
{
	// 初期化したままだとそのままなので、if(!(playerState_ = PLAYER_ID_DEFAULT) PLAYER_ID_DEFAULT)は、なし

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
