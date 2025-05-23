#pragma once
#include "Engine/GameObject.h"
#include <string>
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
	// ���f���֌W
	int hPlayerModel_;
	int hPlayerSwimmingModel_;
	int hPlayerFloatingModel_;
	
	const float playerMoveSpeed_; // Player�̈ړ����x
	int hp_;

	PLAYER_ID playerState_;
	
	// ��]�֌W
	bool isRotateRight_;
	float originalRotateRight_; // �E��]���n�߂��Ƃ��̊p�x��ω���
	bool isRotateLeft_;
	float originalRotateLeft_; // ����]���n�߂��Ƃ��̊p�x��ω���


	// �J�����֌W
	float cameraYaw_; // ���E(Y������)
	float cameraPitch_; // �㉺(X������)
	float cameraDistance_; // �Y�[�������i�����l10�j
	const float initCameraDistance_;// �J�������Z�b�g�p
	const float cameraZoomSpeed_; // �Y�[���X�s�[�h
	const float cameraMinDistance_; // �Y�[���̍ŏ�����
	const float cameraMaxDistance_; // �Y�[���̍ő勗��
	const float cameraRotateSpeed_; // �J�����̉�]���x

	float rotationSpeed_ = 5.0f; // ���W�A��/�b�i�Ⴆ��5.0f�Ȃ�1�b�Ŗ�286�x��]�j
public:
	Player(GameObject* parent);	
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
	
	int GetHp()const{ return hp_; }
	void SetHp(int _hp) { hp_ = _hp; }
	
	void OnCollision(GameObject* pTarget) override;
	// Player�̃|�W�V������Enemy�łƂ��Ă��邽�߂Ɏg�p
	DirectX::XMFLOAT3& GetPosition() { return transform_.position_; }
	
};