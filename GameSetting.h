#pragma once
//-------------------------------------
// Player�ݒ�
//-------------------------------------
#define PLAYER_SPEED					  0.1f // Player�̈ړ����x
#define PLAYER_ROTATE_SPEED				  0.05f // Player�̉�]���x
#define PLAYER_HP_NUMBER_DIGITS_MIN_ARRAY 0 // Player��HP�̌����̍ŏ������̔z��
#define PLAYER_HP_NUMBER_DIGITS_MAX_ARRAY 1 // Player��HP�̌����̍ő包���̔z��
#define PLAYER_HP_NUMBER_DIGITS_MIN       1 // Player��HP�̌����̍ŏ�����
#define PLAYER_HP_MIN                     0 // Player��HP�̍ŏ��l
#define PLAYER_HP_MAX                   999 // Player��HP�̍ő�l
#define PLAYER_HP_DOWN					  1 // Player��HP�̌����l
#define PLAYER_HP_INIT					  5 // Player��HP�̏����l					      5 // Player��HP�̏����l
#define PLAYER_RADIUS					  0.5f //Player�̔��a�i�����蔻��p�j
#define PLAYER_INIT_INVINCIBLE_TIMER_MIN  0.0f //���G���Ԃ̏����l
//-------------------------------------
// HP�֘A
//-------------------------------------
#define CHAR_MIN_INDEX    0
#define CHAR_PER_ROW     16   // 1�s������̕������ichar.png�̉������j
#define CHAR_TOTAL_COUNT 94   // ���p�\�ȕ�����

//-------------------------------------
// Enemy�֘A
//-------------------------------------

//-------------------------------------
// ������ɓ����G
//-------------------------------------
#define SPIRAL_ENEMY_MAX				6 // ������ɓ����G�̍ő吔
#define SPIRAL_ENEMY_ANGLE				0.0f // �����^���̊p�x
#define SPIRAL_ENEMY_ANGULAR_SPEED		1.5f // �����^���̊p�x�̑����X�s�[�h�@1�b�Ԃɉ����W�A����]���邩
#define SPIRAL_ENEMY_RADIUS			   30.0f // �����^���̔��a�@Player����̋���
#define SPIRAL_ENEMY_RADIAL_SPEED		5.0f // �����^���̔��a�̌����X�s�[�h�@1�b�Ԃɉ����[�g���߂Â���
#define SPIRAL_ENEMY_TIME_SINCE_ENTERED	0.0f // Player�͈̔͂ɓ����Ă���̌o�ߎ���
#define SPIRAL_ENEMY_PROXIMITY_RADIUS   5.0f // Enemy�����͈̔͂ɓ�������AenteredProximity_��true�ɂ��ă^�C�}�[���X�^�[�g
#define SPIRAL_ENEMY_DISAPPEAR_AFTER    2.0f // Player�͈̔͂ɓ����Ă��牽�b��ɏ����邩�@timeSinceEntered_�����̒l�ȏ�ɂȂ�����G�����ł�����

#define SPIRAL_ENEMY_MINIMUM_VALUE 20.0f// �����_���̉����l�B���a���Œ�ł�����ɂȂ�
#define SPIRAL_ENEMY_MAXIMUM_VALUE 20.0f// �����_���̕��ł��Brand() �̌��ʂ�0�`1�ɐ��K��������ŁA���̕������v���X�����
#define SPIRAL_ENEMY_MIN_RADIUS     0.5f // Player��Enemy�̍Œᔼ�a

//-------------------------------------
// �����I�ɓ����G
//-------------------------------------
#define STRAIGHT_LINE_ENEMY_MAX            6 // �����I�ɓ����G�̍ő吔
#define STRAIGHT_LINE_ENEMY_SPEED          5.0f // �G�̐i�s���x
#define STRAIGHT_LINE_ENEMY_STOP_RADIUS    0.5f  // ���B���a���x
#define STRAIGHT_LINE_ENEMY_MINIMUM_VALUE 20.0f// �����_���̉����l�B���a���Œ�ł�����ɂȂ�
#define STRAIGHT_LINE_ENEMY_MAXIMUM_VALUE 15.0f// �����_���̕��@rand() �̌��ʂ�0�`1�ɐ��K��������ŁA���̕������v���X�����



//-------------------------------------
// ���̑�
//-------------------------------------
#define INVALID_MODEL_HANDLE 0 // assert(hModel_ >= 0)���f���̓ǂݍ��݂��������Ă��邩�𔻒肷�邽�߂̊�l
#define INVALID_IMAGE_HANDLE 0 // assert(hPict_ >= 0)�摜�̓ǂݍ��݂��������Ă��邩�𔻒肷�邽�߂̊�l
#define INVALID_OBJECT_HANDLE -1 // ��l�摜�⃂�f���̔ԍ��͂O�ȏ�i�O���܂ށj�̒l�ɂȂ�̂�-1

//-------------------------------------
// �}�W�b�N�i���o�[��h�����߂̉��}���u
//-------------------------------------
#define FLOAT_ZERO_THRESHOLD 0.0001f // �������l
#define ZERO                 0.0f    // 0�̒�` �}�W�b�N�i���o�[�h������
#define ONE                  1.0f    // 1�̒�` �}�W�b�N�i���o�[�h������
#define TWO_DEGREES          2.0f    // 2�x�̒�` �}�W�b�N�i���o�[�h������
#define FIVE_DEGREES         5.0f    // 5�x�̒�` �}�W�b�N�i���o�[�h������
#define ALPHA_OPAQUE       255.0f    // ���S�s����