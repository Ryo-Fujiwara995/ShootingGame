#include "SpaceShuttle.h"
#include "Engine/Model.h"
SpaceShuttle::SpaceShuttle(GameObject* parent):GameObject(parent,"SpaceShuttle"),hSpaceShuttleModel_(-1)
{
}

void SpaceShuttle::Initialize()
{
	hSpaceShuttleModel_ = Model::Load("Models\\SpaceShuttle\\SpaceShuttle.fbx");
	assert(hSpaceShuttleModel_ >= 0);
}

void SpaceShuttle::Update()
{
}

void SpaceShuttle::Draw()
{
	transform_.scale_ = XMFLOAT3(0.3f, 0.3f, 0.3f);
	transform_.rotate_.x = 90.0f;
	transform_.position_ = XMFLOAT3(0.0f, 0.3f, -0.8f);
	Model::SetTransform(hSpaceShuttleModel_, transform_);
	Model::Draw(hSpaceShuttleModel_);
}

void SpaceShuttle::Release()
{
}
