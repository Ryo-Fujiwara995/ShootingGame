#include "SpiralEnemy.h"
#include "Engine/Model.h"
#include "Engine/Time.h"

SpiralEnemy::SpiralEnemy(GameObject* parent) :Enemy(parent), hSpiralEnemyDefaultModel_(-1)
{
	
}

void SpiralEnemy::Initialize()
{
	hSpiralEnemyDefaultModel_ = Model::Load("Models\\Enemy\\EnemyDefault.fbx");
	assert(hSpiralEnemyDefaultModel_ >= 0);

    if (!player_) return;

    // プレイヤーの位置を基準に
    const XMFLOAT3& playerPos = player_->GetPosition();

    // ランダムな初期角度（0?2π）
    angle_ = static_cast<float>(rand()) / RAND_MAX * XM_2PI;

    // ランダムな初期距離（例：20～40）
    radius_ = 20.0f + static_cast<float>(rand()) / RAND_MAX * 20.0f;

    // 初期位置を計算
    transform_.position_.x = playerPos.x + cosf(angle_) * radius_;
    transform_.position_.z = playerPos.z + sinf(angle_) * radius_;
    transform_.position_.y = playerPos.y;
}

void SpiralEnemy::Update()
{
    if (!player_) return;

    float deltaTime = Time::GetDeltaTime();
    const XMFLOAT3& playerPos = player_->GetPosition();

    angle_ += angularSpeed_ * deltaTime;
    radius_ -= radialSpeed_ * deltaTime;
    if (radius_ < 0.5f) radius_ = 0.5f;

    transform_.position_.x = playerPos.x + cosf(angle_) * radius_;
    transform_.position_.z = playerPos.z + sinf(angle_) * radius_;
    transform_.position_.y = playerPos.y;
}

void SpiralEnemy::Draw()
{
	Model::SetTransform(hSpiralEnemyDefaultModel_, transform_);
	Model::Draw(hSpiralEnemyDefaultModel_);
}

void SpiralEnemy::Release()
{
}
