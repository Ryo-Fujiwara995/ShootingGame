#pragma once
#include "Engine/GameObject.h"
#include "Player.h"
class HpBar :
    public GameObject
{
private:
	Player* player_ = nullptr;            // �Q�Ɛ�
	int hBackGroundHandle_;      // �w�i�摜�n���h���i����D�F�j
	int hBarHandle_;             // �Q�[�W�{�́i�ԂȂǁj
	float hpRate_;              // �\���p��HP�����i0.0�`1.0�j
public:
	HpBar(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

