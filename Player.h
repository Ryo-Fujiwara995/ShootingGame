#pragma once
#include "Engine/GameObject.h"
enum PLAYER_ID {
	PLAYER_ID_DEFAULT = 0,	// �������
	PLAYER_ID_SWIM = 1,	// �j��
	PLAYER_ID_FLOAT,	// �ӂ�ӂ�
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
	const float RUN_SPEED = 0.5f; // WALK_SPEED���傫���l��

	// ��]�p�̊p�x�ϐ��iPlayer�N���X�ɒǉ����Ă��������j
	float cameraYaw_ = 0.0f;
	float cameraPitch_ = 0.0f;
	float cameraDistance_ = 10.0f; // �� �ǉ��F�Y�[�������i�����l10�j
	const float initCameraDistance_ = 10.0f;// �J�������Z�b�g�p
public:
	Player(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
	
	// Player�̃|�W�V�������O�łƂ��Ă��邽�߂Ɏg�p
	DirectX::XMFLOAT3& GetPosition() { return transform_.position_; }
	
};