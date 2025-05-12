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
	Model::SetTransform(hSpaceShuttleModel_, transform_);
	Model::Draw(hSpaceShuttleModel_);
}

void SpaceShuttle::Release()
{
}
