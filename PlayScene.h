#pragma once
#include "Engine/GameObject.h"
#include "Player.h"
class PlayScene : public GameObject
{
private:
	int hPict_;

	float enemySpawnTimer_ = 0.0f;// �����Ԋu�^�C�}�[
	float enemySpawnInterval_ = 2.0f;// 5�b���ƂɓG�𐶐�
	Player* player_ = nullptr;
public:
	PlayScene(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};