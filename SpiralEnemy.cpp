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

    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 0.5f);
    AddCollider(collision);

    if (!player_) return;

    // Playerの現在位置をロックオン座標として記憶する
    targetPos_ = player_->GetPosition();

    // ランダムな初期角度（0 2π）と距離
    angle_ = static_cast<float>(rand()) / RAND_MAX * XM_2PI;
    radius_ = SPIRAL_ENEMY_MINIMUM_VALUE + static_cast<float>(rand()) / RAND_MAX * SPIRAL_ENEMY_MAXIMUM_VALUE;

    // 初期位置を計算
    transform_.position_.x = targetPos_.x + cosf(angle_) * radius_;
    transform_.position_.z = targetPos_.z + sinf(angle_) * radius_;
    transform_.position_.y = targetPos_.y;
}

void SpiralEnemy::Update()
{
    if (!player_) return;

    float deltaTime = Time::GetDeltaTime();

    // 螺旋移動
    angle_ += angularSpeed_ * deltaTime;
    radius_ -= radialSpeed_ * deltaTime;
    if (radius_ < SPIRAL_ENEMY_MIN_RADIUS) radius_ = SPIRAL_ENEMY_MIN_RADIUS;

    // 位相を進める
    verticalPhase_ += verticalFrequency_ * deltaTime;
    float verticalOffset = sinf(verticalPhase_) * verticalAmplitude_;

    // ロックオン位置を中心に、螺旋移動
    transform_.position_.x = targetPos_.x + cosf(angle_) * radius_;
    transform_.position_.z = targetPos_.z + sinf(angle_) * radius_;
    transform_.position_.y = targetPos_.y;

    // Playerの半径5の範囲に入った後のX秒後に消滅
    // Playerとの距離をチェック
    float dx = transform_.position_.x - targetPos_.x;
    float dz = transform_.position_.z - targetPos_.z;
    float distSq = (dx * dx) + (dz * dz);

    if (distSq <= proximityRadius * proximityRadius) {
        // ロックオン位置に入った
        // Playerとの現在位置を計算
        float px = transform_.position_.x - player_->GetPosition().x;
        float pz = transform_.position_.z - player_->GetPosition().z;
        float playerDistSq = (px * px) + (pz * pz);

        // 実際の衝突判定と同じ || 少し小さめの半径を使う
        const float playerCollisionRadius = 1.0f;

        // Playerと接触していない場合のみ消滅タイマー進行
        if (playerDistSq > playerCollisionRadius * playerCollisionRadius) {
            if (!enteredProximity_) {
                enteredProximity_ = true;
                timeSinceEntered_ = 0.0f;
            }
            else {
                timeSinceEntered_ += deltaTime;
                if (timeSinceEntered_ >= disappearAfter) {
                    KillMe(); // プレイヤー範囲に入ってからX秒後に消滅
                    //OnCollision(player_); // プレイヤーに衝突したら自分を削除
                }
            }
        }
        else {
            // Playerの範囲から出た
            enteredProximity_ = false;
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

