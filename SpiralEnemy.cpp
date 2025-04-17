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

    // �v���C���[�̈ʒu�����
    const XMFLOAT3& playerPos = player_->GetPosition();

    // �����_���ȏ����p�x�i0 2�΁j
    angle_ = static_cast<float>(rand()) / RAND_MAX * XM_2PI;

    // �����_���ȏ��������i��F20�`40�j
    radius_ = 20.0f + static_cast<float>(rand()) / RAND_MAX * 20.0f;

    // �����ʒu���v�Z
    transform_.position_.x = playerPos.x + cosf(angle_) * radius_;
    transform_.position_.z = playerPos.z + sinf(angle_) * radius_;
    transform_.position_.y = playerPos.y;
}

void SpiralEnemy::Update()
{
    if (!player_) return;

    float deltaTime = Time::GetDeltaTime();
    const XMFLOAT3& playerPos = player_->GetPosition();

    // �����ړ�
    angle_ += angularSpeed_ * deltaTime;
    radius_ -= radialSpeed_ * deltaTime;
    if (radius_ < 0.5f) radius_ = 0.5f;

    transform_.position_.x = playerPos.x + cosf(angle_) * radius_;
    transform_.position_.z = playerPos.z + sinf(angle_) * radius_;
    transform_.position_.y = playerPos.y;

    // Player�̔��a5�͈̔͂ɓ��������X�b��ɏ���
    // Player�Ƃ̋������`�F�b�N
    float dx = transform_.position_.x - playerPos.x;
    float dz = transform_.position_.z - playerPos.z;
    float distSq = (dx * dx) + (dz * dz);

    if (distSq <= PROXIMITY_RADIUS * PROXIMITY_RADIUS) {
        if (!enteredProximity_) {
            enteredProximity_ = true;
            timeSinceEntered_ = 0.0f;
        }
        else {
            timeSinceEntered_ += deltaTime;
            if (timeSinceEntered_ >= DISAPPEAR_AFTER) {
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
