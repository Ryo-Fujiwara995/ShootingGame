#include "GameOverScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/Audio.h"
GameOverScene::GameOverScene(GameObject* parent) : GameObject(parent, "TitleScene"), hGameOverPict_(-1)
{
}

void GameOverScene::Initialize()
{
	hGameOverPict_ = Image::Load("Images\\GameOverScene\\GameOver.png");
	assert(hGameOverPict_ >= 0);

	hGameOverSceneSound_ = Audio::Load("Bgm\\GameOverScene\\GameOverScene.wav");
	assert(hGameOverSceneSound_ >= 0);
}

void GameOverScene::Update()
{
	if (Input::IsKey(DIK_RETURN)) {
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TITLE);
	}
}

void GameOverScene::Draw()
{
	Image::SetTransform(hGameOverPict_, transform_);
	Image::Draw(hGameOverPict_);

	Audio::Play(hGameOverSceneSound_);
}

void GameOverScene::Release()
{
}
