#include "PlayScene.h"
#include "Player.h"
#include "SpaceShuttle.h"
#include "SpiralEnemy.h"
#include "StraightLineEnemy.h"
#include "Engine/Image.h"
#include "GameSetting.h"

#include "Engine/VFX.h"
#include "Engine/SceneManager.h"
#include "Engine/Debug.h"
#include "Engine/Input.h"

#include "TitleScene.h"
PlayScene::PlayScene(GameObject* parent):GameObject(parent),hPict_(-1)
{
}

void PlayScene::Initialize()
{	
	// �w�i
	hPict_ = Image::Load("Images\\space.png");
	 Instantiate<SpaceShuttle>(this);
	Player * player = Instantiate<Player>(this);
	
	//�w�i�ɐ���ǉ�
	EmitterData  starEffect;
	starEffect.textureFileName = "Paticle\\flashC_Y.png";
	starEffect.position = XMFLOAT3(0.0f, 5.0f, 0.0f); // �����̋󒆂�����
	starEffect.positionRnd = XMFLOAT3(3.0f, 1.0f, 3.0f); // �����_���ɂ΂�܂��͈�
	starEffect.size = XMFLOAT2(0.2f, 0.2f); // ������
	starEffect.sizeRnd = XMFLOAT2(0.5f, 0.5f); // �T�C�Y�̂΂��
	starEffect.color = XMFLOAT4(1, 1, 1, 1); // ���F
	starEffect.deltaColor = XMFLOAT4(0, 0, 0, -0.05f); // ���X�ɓ�����
	starEffect.lifeTime = 30; // �����F30�t���[��
	starEffect.delay = 5; // 5�t���[�����Ƃɔ���
	starEffect.number = 1; // ����1����
	starEffect.isBillBoard = true; // �r���{�[�h�ŕ`��
	VFX::Start(starEffect);


	// 10�b���Ƃɂǂ��炩�𐶐�����\��
	for (int i = 0; i < SPIRAL_ENEMY_MAX; i++) {
		auto spiralEnemy = Instantiate<SpiralEnemy>(this);
		spiralEnemy->player_ = player;	// �e�G�ɋ��ʂ�Player��ݒ�
		spiralEnemy->Initialize();		// �e�G�Ƀ����_���ȏ����ʒu��ݒ�
	}

	//for (int j = 0; j < STRAIGHT_LINE_ENEMY_MAX; j++) {
	//	auto straightLineEnemy = Instantiate<StraightLineEnemy>(this);
	//	straightLineEnemy->player_ = player;
	//	straightLineEnemy->Initialize();
	//}

}

void PlayScene::Update()
{
}

void PlayScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

void PlayScene::Release()
{
}
