#pragma once
#include "Engine/GameObject.h"
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
	int hPlayerModel_;
	int hPlayerSwimmingModel_;
	int hPlayerFloatingModel_;
	PLAYER_ID playerState_;
	bool isRotateRight_;
	float originalRotateRight_;

	bool isRotateLeft_;
	float originalRotateLeft_;

	const float WALK_SPEED = 0.2f;
	const float RUN_SPEED = 0.5f; // WALK_SPEEDより大きい値に

	// 回転用の角度変数（Playerクラスに追加してください）
	float cameraYaw_ = 0.0f;
	float cameraPitch_ = 0.0f;
	float cameraDistance_ = 10.0f; // ← 追加：ズーム距離（初期値10）
	const float initCameraDistance_ = 10.0f;// カメラリセット用
public:
	Player(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
	
	// Playerのポジションを外でとってくるために使用
	DirectX::XMFLOAT3& GetPosition() { return transform_.position_; }
	
};