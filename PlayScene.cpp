#include "PlayScene.h"
#include "SpaceShuttle.h"
#include "SpiralEnemy.h"
#include "StraightLineEnemy.h"
#include "Engine/Image.h"
#include "GameSetting.h"

#include "Engine/VFX.h"
#include "Engine/SceneManager.h"
#include "Engine/Debug.h"
#include "Engine/Input.h"
#include "Engine/Time.h"
#include "Engine/Audio.h"

#include "TitleScene.h"
#include <sstream>
#include <iomanip>
const int CHAR_WIDTH = 16;
const int CHAR_HEIGHT = 16;
//const int CHAR_PER_ROW = 16;
const int CHAR_START_CODE = 32;
PlayScene::PlayScene(GameObject* parent):GameObject(parent),hPict_(-1), hCountDownTimerPict_(-1)
{
}
void PlayScene::Initialize()
{	
	
	// �w�i
	hPict_ = Image::Load("Images\\PlayScene\\PlaySceneBack.png");
	assert(hPict_ >= INVALID_IMAGE_HANDLE);
	hCountDownTimerPict_ = Image::Load("char.png");
	assert(hCountDownTimerPict_ >= INVALID_IMAGE_HANDLE);

	player_ = Instantiate<Player>(this);

	hPlaySceneSound_ = Audio::Load("Bgm\\PlayScene\\PlayScene.wav");
	assert(hPlaySceneSound_ >= 0);
}

void PlayScene::Update()
{
	float dt = Time::GetDeltaTime();
	// ����������ꂽ�I�I���N���A
	elapsedTime_ += dt;
	if (elapsedTime_ >= timeLimit_) {
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_CLEAR);
	}

	enemySpawnTimer_ += dt;

	if (enemySpawnTimer_ >= enemySpawnInterval_) {
		enemySpawnTimer_ = 0.0f;

		int randVal = rand() % 2; // 0 or 1

		if (randVal == 0) {
			auto spiralEnemy = Instantiate<SpiralEnemy>(this);
			spiralEnemy->player_ = player_;
			spiralEnemy->Initialize();
		}
		else {
			auto straightEnemy = Instantiate<StraightLineEnemy>(this);
			straightEnemy->player_ = player_;
			straightEnemy->Initialize();
		}
	}
}



void PlayScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);

	Audio::Play(hPlaySceneSound_);
	// ----------- �^�C�}�[�`�� -----------
		// �c�莞�Ԃ̌v�Z�i�ő�60�b�j
	int remainTime = static_cast<int>(timeLimit_ - elapsedTime_);
	if (remainTime < 0) remainTime = 0;

	// �c�莞�Ԃ�2��������ցi��: "05"�j
	std::ostringstream oss;
	oss << std::setw(2) << std::setfill('0') << remainTime;
	std::string timeStr = oss.str();  // 2���� "00" �` "60"

	// 1�������`��
	for (int i = 0; i < 2; i++) {
		char c = timeStr[i];
		int index = static_cast<int>(c) - CHAR_START_CODE;

		if (index >= CHAR_MIN_INDEX && index < CHAR_TOTAL_COUNT) {
			int srcX = (index % CHAR_PER_ROW) * CHAR_WIDTH;
			int srcY = (index / CHAR_PER_ROW) * CHAR_HEIGHT;

			Transform drawTransform = transform_;
			drawTransform.position_.x += 20 + i * CHAR_WIDTH; // �\���J�n�ʒu + �����炵
			drawTransform.position_.y += 20;
			Image::SetTransform(hCountDownTimerPict_, drawTransform); Image::Draw(hCountDownTimerPict_);
			Image::SetRect(hCountDownTimerPict_, srcX, srcY, CHAR_WIDTH, CHAR_HEIGHT);
			Image::SetAlpha(hCountDownTimerPict_, 255); // �O�̂��ߒǉ�
			Image::ResetRect(hCountDownTimerPict_);
		}
	}
}

void PlayScene::Release()
{
}
