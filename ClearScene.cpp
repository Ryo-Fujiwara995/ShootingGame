#include "ClearScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/Audio.h"
ClearScene::ClearScene(GameObject* parent)
{
}

void ClearScene::Initialize()
{
	hClearPict_ = Image::Load("Images\\ClearScene\\Clear.png");
	hClearSceneSound_ = Audio::Load("Bgm\\ClearScene\\ClearScene.wav");
	assert(hClearSceneSound_ >= 0);
}

void ClearScene::Update()
{
	if (Input::IsKey(DIK_RETURN)) {
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TITLE);
	}
}

void ClearScene::Draw()
{
	Image::SetTransform(hClearPict_, transform_);
	Image::Draw(hClearPict_);

	Audio::Play(hClearSceneSound_);
}

void ClearScene::Release()
{
}
