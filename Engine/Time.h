#pragma once
#include <windows.h>

class Time
{
public:
    static void Initialize();      // �J�n���ɌĂяo��
    static void Update();          // ���t���[���X�V
    static float GetDeltaTime();   // �O�t���[������̌o�ߎ��ԁi�b�j
	static void AllRelease();      // �I�����ɌĂяo��

private:
    static LARGE_INTEGER frequency_;
    static LARGE_INTEGER previousTime_;
    static float deltaTime_;
};
