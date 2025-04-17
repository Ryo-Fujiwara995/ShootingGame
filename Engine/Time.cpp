#include "Time.h"
#include <windows.h>

namespace Time {
    static LARGE_INTEGER frequency;
    static LARGE_INTEGER prevCounter;
    static float deltaTime = 0.0f;

    void Initialize() {
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&prevCounter);
    }

    void Update() {
        LARGE_INTEGER current;
        QueryPerformanceCounter(&current);
        deltaTime = static_cast<float>(current.QuadPart - prevCounter.QuadPart) / frequency.QuadPart;
        prevCounter = current;
    }

    float GetDeltaTime() {
        return deltaTime;
    }
}
