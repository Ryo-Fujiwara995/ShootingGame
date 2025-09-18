#pragma once
#include "../../../Engine/GameObject.h"
#include <string>
//enum PLAYER_ID {
//	PLAYER_ID_DEFAULT = 0,	// 初期状態
//	PLAYER_ID_SWIM = 1,	// 泳ぐ
//	PLAYER_ID_FLOAT,	// ふよふよ
//	PLAYER_ID_MAX
//};

class Player :
    public GameObject
{
private:
	//画像関係
	int hDamagePict_; // ダメージ時の赤い画面

	// モデル関係
	int hPlayerModel_;
	
	int hp_;

	float invincibleTimer_ = 0.0f;      // 無敵タイマー
	const float invincibleTime_ = 2.0f; // 無敵時間（秒）
	
	float damageFlashTimer_ = 0.0f;
	const float damageFlashDuration_ = 0.5f; // フェードの時間（秒）
	const float damageFlashHold_ = 0.06f; // 先頭の赤色を維持する時間（秒）
	bool isDamageFlashing_ = false;

	//PLAYER_ID playerState_;

	// カメラ関係
	float cameraYaw_; // 左右(Y軸周り)
	float cameraPitch_; // 上下(X軸周り)
	float cameraDistance_; // ズーム距離（初期値10）
	const float initCameraYaw_ = 0.0f;     // 初期Yaw角
	const float initCameraPitch_ = 0.0f;   // 初期Pitch角
	const float initCameraDistance_; // 初期距離
	const float cameraZoomSpeed_; // ズームスピード

	float rotationSpeed_ = 5.0f; // ラジアン/秒（例えば5.0fなら1秒で約286度回転）
public:
	Player(GameObject* parent);	
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
	
	int GetHp()const{ return hp_; }
	void SetHp(int _hp) { hp_ = _hp; }
	
	void OnCollision(GameObject* pTarget) override;
	// PlayerのポジションをEnemyでとってくるために使用
	XMFLOAT3& GetPosition() { return transform_.position_; }
};