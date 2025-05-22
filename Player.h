#pragma once
#include "Engine/GameObject.h"
#include <string>
enum PLAYER_ID {
	PLAYER_ID_DEFAULT = 0,	// 初期状態
	PLAYER_ID_SWIM = 1,	// 泳ぐ
	PLAYER_ID_FLOAT,	// ふよふよ
	PLAYER_ID_MAX
};
class Player :
    public GameObject
{

private:
	// モデル関係
	int hPlayerModel_;
	int hPlayerSwimmingModel_;
	int hPlayerFloatingModel_;
	
	const float playerMoveSpeed_; // Playerの移動速度
	int hp_;

	PLAYER_ID playerState_;
	
	// 回転関係
	bool isRotateRight_;
	float originalRotateRight_; // 右回転を始めたときの角度や変化量
	bool isRotateLeft_;
	float originalRotateLeft_; // 左回転を始めたときの角度や変化量


	// カメラ関係
	float cameraYaw_; // 左右(Y軸周り)
	float cameraPitch_; // 上下(X軸周り)
	float cameraDistance_; // ズーム距離（初期値10）
	const float initCameraDistance_;// カメラリセット用
	const float cameraZoomSpeed_; // ズームスピード
	const float cameraMinDistance_; // ズームの最小距離
	const float cameraMaxDistance_; // ズームの最大距離
	const float cameraRotateSpeed_; // カメラの回転速度

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
	DirectX::XMFLOAT3& GetPosition() { return transform_.position_; }
	
};