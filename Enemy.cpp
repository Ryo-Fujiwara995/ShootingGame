#include "Enemy.h"
#include "Engine/Model.h"

Enemy::Enemy(GameObject* parent):GameObject(parent ,"Enemy"),hEnemyModel_(-1)
{
}

void Enemy::Initialize()
{
	hEnemyModel_ = Model::Load("Models\\Enemy\\EnemyDefault.fbx");
	assert(hEnemyModel_ >= 0);
}

void Enemy::Update()
{
}

void Enemy::Draw()
{
	Model::SetTransform(hEnemyModel_, transform_);
	Model::Draw(hEnemyModel_);
}

void Enemy::Release()
{
}
