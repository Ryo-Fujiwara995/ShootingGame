#include "SpiralEnemy.h"
#include "Engine/Model.h"
#include "Engine/Time.h"

SpiralEnemy::SpiralEnemy(GameObject* parent) :GameObject(parent, "SpiralEnemy"), hSpiralEnemyDefaultModel_(-1)
{
}

void SpiralEnemy::Initialize()
{
    hSpiralEnemyDefaultModel_ = Model::Load("Models\\Enemy\\EnemyDefault.fbx");
    assert(hSpiralEnemyDefaultModel_ >= INVALID_MODEL_HANDLE);

    if (!player_) return;

    // プレイヤーの位置を基準に
    const XMFLOAT3& playerPos = player_->GetPosition();

    // ランダムな初期角度（0 2π）
    angle_ = static_cast<float>(rand()) / RAND_MAX * XM_2PI;

    // ランダムな初期距離
    radius_ = SPIRAL_ENEMY_MINIMUM_VALUE + static_cast<float>(rand()) / RAND_MAX * SPIRAL_ENEMY_MAXIMUM_VALUE;

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


    // 螺旋移動
    angle_ += angularSpeed_ * deltaTime;
    radius_ -= radialSpeed_ * deltaTime;
    if (radius_ < SPIRAL_ENEMY_MIN_RADIUS) radius_ = SPIRAL_ENEMY_MIN_RADIUS;

    transform_.position_.x = playerPos.x + cosf(angle_) * radius_;
    transform_.position_.z = playerPos.z + sinf(angle_) * radius_;
    transform_.position_.y = playerPos.y;

    // Playerの半径5の範囲に入った後のX秒後に消滅
    // Playerとの距離をチェック
    float dx = transform_.position_.x - playerPos.x;
    float dz = transform_.position_.z - playerPos.z;
    float distSq = (dx * dx) + (dz * dz);

    if (distSq <= proximityRadius * proximityRadius) {
        if (!enteredProximity_) {
            enteredProximity_ = true;
            timeSinceEntered_ = 0.0f;
        }
        else {
            timeSinceEntered_ += deltaTime;
            if (timeSinceEntered_ >= disappearAfter) {
                KillMe();
            }
        }
    }
}

void SpiralEnemy::Draw()
{
	Model::SetTransform(hSpiralEnemyDefaultModel_, transform_);
	Model::Draw(hSpiralEnemyDefaultModel_);
    
}

void SpiralEnemy::Release()
{
}
