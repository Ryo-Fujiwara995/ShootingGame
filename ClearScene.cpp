#include "ClearScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
ClearScene::ClearScene(GameObject* parent)
{
}

void ClearScene::Initialize()
{
	hClearPict_ = Image::Load("Images\\ClearScene\\Clear.png");
	
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
}

void ClearScene::Release()
{
}
