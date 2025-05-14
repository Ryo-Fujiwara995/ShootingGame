#include "StraightLineEnemy.h"
#include "Engine/Model.h"
#include "Engine/Time.h"
#include <cmath>
#include <cstdlib> // rand()
StraightLineEnemy::StraightLineEnemy(GameObject* parent) :GameObject(parent, "StraightLineEnemy")
        ,hStraightLineEnemyModel_(-1)
{
}

void StraightLineEnemy::Initialize()
{
    hStraightLineEnemyModel_ = Model::Load("Models\\Enemy\\EnemyStraightLine.fbx");
	assert(hStraightLineEnemyModel_ >= INVALID_MODEL_HANDLE);

    SphereCollider* collider = new SphereCollider(XMFLOAT3(0, 0, 0), 1.2f);
    AddCollider(collider);

    if (!player_) return;

    // プレイヤー位置取得
    const XMFLOAT3& playerPos = player_->GetPosition();

    // ランダムな角度・半径で初期位置を決める
    float angle = static_cast<float>(rand()) / RAND_MAX * XM_2PI; // 0〜2π
    float radius = STRAIGHT_LINE_ENEMY_MINIMUM_VALUE + static_cast<float>(rand()) / RAND_MAX * STRAIGHT_LINE_ENEMY_MAXIMUM_VALUE; // 20〜35

    transform_.position_.x = playerPos.x + cosf(angle) * radius;
    transform_.position_.z = playerPos.z + sinf(angle) * radius;
    transform_.position_.y = playerPos.y; // 2Dならy固定でOK

    // ロックオン
    targetPos_ = playerPos;
    lockedOn_ = true;
}

void StraightLineEnemy::Update()
{
    if (!lockedOn_) return;

    float dt = Time::GetDeltaTime();
    elapsedTime_ += dt; // 時間を加算

    if (elapsedTime_ >= lifeTime_) {
        KillMe(); // 5秒経過したら自動で全部削除
    }

    XMFLOAT3& myPos = transform_.position_;

    // ロックオン位置へのベクトル
    XMFLOAT3 dir = {
        targetPos_.x - myPos.x,
        targetPos_.y - myPos.y,
        targetPos_.z - myPos.z
    };

    float distSq = dir.x * dir.x + dir.y * dir.y + dir.z * dir.z;

    float len = sqrtf(distSq);
    if (len > FLOAT_ZERO_THRESHOLD) {
        dir.x /= len;
        dir.y /= len;
        dir.z /= len;

        myPos.x += dir.x * speed_ * dt;
        myPos.y += dir.y * speed_ * dt;
        myPos.z += dir.z * speed_ * dt;
    }
}

void StraightLineEnemy::Draw()
{
	Model::SetTransform(hStraightLineEnemyModel_, transform_);
	Model::Draw(hStraightLineEnemyModel_);
}

void StraightLineEnemy::Release()
{
}

void StraightLineEnemy::OnCollision(GameObject* pTarget)
{
	if (pTarget->GetObjectName() == "Player") {
		KillMe();
	}
}
