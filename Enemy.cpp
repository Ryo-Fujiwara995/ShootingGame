#include "Enemy.h"
#include "Engine/Model.h"

Enemy::Enemy(GameObject* parent):GameObject(parent ,"Enemy"), hEnemyDefaultModel_(-1)
{
}

void Enemy::Initialize()
{
	hEnemyDefaultModel_ = Model::Load("Models\\Enemy\\EnemyDefault.fbx");
	assert(hEnemyDefaultModel_ >= 0);
}

void Enemy::Update()
{
}

void Enemy::Draw()
{
	Model::SetTransform(hEnemyDefaultModel_, transform_);
	Model::Draw(hEnemyDefaultModel_);
}

void Enemy::Release()
{
}
