#include "Time.h"

LARGE_INTEGER Time::frequency_;
LARGE_INTEGER Time::previousTime_;
float Time::deltaTime_ = 0.0f;

void Time::Initialize()
{
    QueryPerformanceFrequency(&frequency_);
    QueryPerformanceCounter(&previousTime_);
}

void Time::Update()
{
    LARGE_INTEGER currentTime;
    QueryPerformanceCounter(&currentTime);

    deltaTime_ = static_cast<float>(currentTime.QuadPart - previousTime_.QuadPart) / frequency_.QuadPart;
    previousTime_ = currentTime;
}

float Time::GetDeltaTime()
{
    return deltaTime_;
}

void Time::AllRelease()
{
    previousTime_.QuadPart = 0;
    deltaTime_ = 0.0f;
}
