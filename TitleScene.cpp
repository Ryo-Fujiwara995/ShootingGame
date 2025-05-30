#include "TitleScene.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/Audio.h"
#include "Engine/SceneManager.h"
TitleScene::TitleScene(GameObject* parent) : GameObject(parent, "TitleScene"), hTitlePict_(-1)
{
}

void TitleScene::Initialize()
{
	hTitlePict_ = Image::Load("Images\\TitleScene\\Title.png");
	assert(hTitlePict_ >= 0);

	hTitleSound_ = Audio::Load("Bgm\\TitleScene\\Title.wav");
	assert(hTitleSound_ >= 0);
}

void TitleScene::Update()
{
	if (Input::IsKey(XINPUT_GAMEPAD_A) || Input::IsKey(DIK_RETURN)) {
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_PLAY);
	}
}

void TitleScene::Draw()
{
	Image::SetTransform(hTitlePict_, transform_);
	Image::Draw(hTitlePict_);

	Audio::Play(hTitleSound_);
}

void TitleScene::Release()
{
}
