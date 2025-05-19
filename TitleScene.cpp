#include "TitleScene.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
TitleScene::TitleScene(GameObject* parent) : GameObject(parent, "TitleScene"), hPict_(-1)
{
}

void TitleScene::Initialize()
{
	hPict_ = Image::Load("Images\\Title.png");
	assert(hPict_ >= 0);
}

void TitleScene::Update()
{
	if (Input::IsKey(XINPUT_GAMEPAD_A) || Input::IsKey(DIK_A)) {
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_PLAY);
	}// XBoxコントローラを使っています。LTボタンと、 Rtボタンを使いたいです。まずは、コンソールで確認したいです
}

void TitleScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

void TitleScene::Release()
{
}
