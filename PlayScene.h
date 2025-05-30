#pragma once
#include "Engine/GameObject.h"
#include "Player.h"
class PlayScene : public GameObject
{
private:
	int hPict_;
	int hCountDownTimerPict_;
	int hPlaySceneSound_;

	float enemySpawnTimer_ = 0.0f;// �����Ԋu�^�C�}�[
	float enemySpawnInterval_ = 2.0f;// 5�b���ƂɓG�𐶐�
	Player* player_ = nullptr;

	float timeLimit_ = 10.0f;      // �������ԁi�b�j
	float elapsedTime_ = 0.0f;     // �o�ߎ���

	const int CHAR_WIDTH = 16;
	const int CHAR_HEIGHT = 16;
	const int CHAR_PER_ROW = 16;
	const int CHAR_START_CODE = 32;

public:
	PlayScene(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};