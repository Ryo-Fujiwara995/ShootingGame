#include "GameOverScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
GameOverScene::GameOverScene(GameObject* parent) : GameObject(parent, "TitleScene"), hGameOverPict_(-1)
{
}

void GameOverScene::Initialize()
{
	hGameOverPict_ = Image::Load("Images\\GameOverScene\\GameOver.png");
	assert(hGameOverPict_ >= 0);
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
}

void GameOverScene::Release()
{
}
