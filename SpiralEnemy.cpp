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

    // Player�̌��݈ʒu�����b�N�I�����W�Ƃ��ċL������
    targetPos_ = player_->GetPosition();

    // �����_���ȏ����p�x�i0 2�΁j�Ƌ���
    angle_ = static_cast<float>(rand()) / RAND_MAX * XM_2PI;
    radius_ = SPIRAL_ENEMY_MINIMUM_VALUE + static_cast<float>(rand()) / RAND_MAX * SPIRAL_ENEMY_MAXIMUM_VALUE;

    // �����ʒu���v�Z
    transform_.position_.x = targetPos_.x + cosf(angle_) * radius_;
    transform_.position_.z = targetPos_.z + sinf(angle_) * radius_;
    transform_.position_.y = targetPos_.y;
}

void SpiralEnemy::Update()
{
    if (!player_) return;

    float deltaTime = Time::GetDeltaTime();

    // �����ړ�
    angle_ += angularSpeed_ * deltaTime;
    radius_ -= radialSpeed_ * deltaTime;
    if (radius_ < SPIRAL_ENEMY_MIN_RADIUS) radius_ = SPIRAL_ENEMY_MIN_RADIUS;

    // �ʑ���i�߂�
    verticalPhase_ += verticalFrequency_ * deltaTime;
    float verticalOffset = sinf(verticalPhase_) * verticalAmplitude_;

    // ���b�N�I���ʒu�𒆐S�ɁA�����ړ�
    transform_.position_.x = targetPos_.x + cosf(angle_) * radius_;
    transform_.position_.z = targetPos_.z + sinf(angle_) * radius_;
    transform_.position_.y = targetPos_.y;

    // Player�̔��a5�͈̔͂ɓ��������X�b��ɏ���
    // Player�Ƃ̋������`�F�b�N
    float dx = transform_.position_.x - targetPos_.x;
    float dz = transform_.position_.z - targetPos_.z;
    float distSq = (dx * dx) + (dz * dz);

    if (distSq <= proximityRadius * proximityRadius) {
        // ���b�N�I���ʒu�ɓ�����
        // Player�Ƃ̌��݈ʒu���v�Z
        float px = transform_.position_.x - player_->GetPosition().x;
        float pz = transform_.position_.z - player_->GetPosition().z;
        float playerDistSq = (px * px) + (pz * pz);

        // ���ۂ̏Փ˔���Ɠ��� || ���������߂̔��a���g��
        const float playerCollisionRadius = 1.0f;

        // Player�ƐڐG���Ă��Ȃ��ꍇ�̂ݏ��Ń^�C�}�[�i�s
        if (playerDistSq > playerCollisionRadius * playerCollisionRadius) {
            if (!enteredProximity_) {
                enteredProximity_ = true;
                timeSinceEntered_ = 0.0f;
            }
            else {
                timeSinceEntered_ += deltaTime;
                if (timeSinceEntered_ >= disappearAfter) {
                    KillMe(); // �v���C���[�͈͂ɓ����Ă���X�b��ɏ���
                    //OnCollision(player_); // �v���C���[�ɏՓ˂����玩�����폜
                }
            }
        }
        else {
            // Player�͈̔͂���o��
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

