//-------------------------------------
// Player�ݒ�
//-------------------------------------
//#define PLAYER_SPEED 0.1f // Player�̈ړ����x
//#define PLAYER_ROTATE_SPEED 0.05f // Player�̉�]���x
//-------------------------------------
// Enemy�֘A
//-------------------------------------

//-------------------------------------
// ������ɓ����G
//-------------------------------------
#define SPIRAL_ENEMY_MAX 6 // ������ɓ����G�̍ő吔
#define SPIRAL_ENEMY_ANGLE 0.0f // �����^���̊p�x
#define SPIRAL_ENEMY_ANGULAR_SPEED 1.5f // �����^���̊p�x�̑����X�s�[�h�@1�b�Ԃɉ����W�A����]���邩
#define SPIRAL_ENEMY_RADIUS 30.0f // �����^���̔��a�@Player����̋���
#define SPIRAL_ENEMY_RADIAL_SPEED 5.0f // �����^���̔��a�̌����X�s�[�h�@1�b�Ԃɉ����[�g���߂Â���
#define SPIRAL_ENEMY_TIME_SINCE_ENTERED 0.0f // Player�͈̔͂ɓ����Ă���̌o�ߎ���
#define SPIRAL_ENEMY_PROXIMITY_RADIUS 5.0f // Enemy�����͈̔͂ɓ�������AenteredProximity_��true�ɂ��ă^�C�}�[���X�^�[�g
#define SPIRAL_ENEMY_DISAPPEAR_AFTER 2.0f // Player�͈̔͂ɓ����Ă��牽�b��ɏ����邩�@timeSinceEntered_�����̒l�ȏ�ɂȂ�����G�����ł�����

#define SPIRAL_ENEMY_MINIMUM_VALUE 20.0f// �����_���̉����l�B���a���Œ�ł�����ɂȂ�
#define SPIRAL_ENEMY_MAXIMUM_VALUE 20.0f// �����_���̕��ł��Brand() �̌��ʂ�0�`1�ɐ��K��������ŁA���̕������v���X�����
#define SPIRAL_ENEMY_MIN_RADIUS 0.5f // Player��Enemy�̍Œᔼ�a

//-------------------------------------
// �����I�ɓ����G
//-------------------------------------
#define STRAIGHT_LINE_ENEMY_MAX 6 // �����I�ɓ����G�̍ő吔
#define STRAIGHT_LINE_ENEMY_SPEED 5.0f // �G�̐i�s���x
#define STRAIGHT_LINE_ENEMY_STOP_RADIUS 0.5f  // ���B���a���x
#define STRAIGHT_LINE_ENEMY_MINIMUM_VALUE 20.0f// �����_���̉����l�B���a���Œ�ł�����ɂȂ�
#define STRAIGHT_LINE_ENEMY_MAXIMUM_VALUE 15.0f// �����_���̕��@rand() �̌��ʂ�0�`1�ɐ��K��������ŁA���̕������v���X�����

//-------------------------------------
// ���̑�
//-------------------------------------
#define INVALID_MODEL_HANDLE 0 // assert(hModel_ >= 0)���f���̓ǂݍ��݂��������Ă��邩�𔻒肷�邽�߂̊�l
#define FLOAT_ZERO_THRESHOLD 0.0001f // �������l

