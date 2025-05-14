#pragma once
#include <windows.h>

class Time
{
public:
    static void Initialize();      // 開始時に呼び出す
    static void Update();          // 毎フレーム更新
    static float GetDeltaTime();   // 前フレームからの経過時間（秒）
	static void AllRelease();      // 終了時に呼び出す

private:
    static LARGE_INTEGER frequency_;
    static LARGE_INTEGER previousTime_;
    static float deltaTime_;
};
