#include "WindowsClockManager.hpp"
#include <windows.h>
#include <thread> // Optional for finer control over sleep (e.g., std::this_thread::sleep_for)

WindowsClockManager::WindowsClockManager() noexcept
{
    mTargetFrameDuration = 0;
    mLastSyncTime = 0;
}

double WindowsClockManager::getCurrentTime() const {
    LARGE_INTEGER frequency, counter;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&counter);
    return static_cast<double>(counter.QuadPart) / (frequency.QuadPart / 1000.0); // Milliseconds
}

void WindowsClockManager::sleep(double milliseconds) const {
    Sleep(static_cast<DWORD>(milliseconds));
}

void WindowsClockManager::setTargetFrameRate(int fps) {
    mTargetFrameDuration = 1000.0 / fps; // Set frame duration in milliseconds
}

void WindowsClockManager::synchronizeFrame() {
    double currentTime = getCurrentTime();
    double timeSinceLastSync = currentTime - mLastSyncTime;

    if (timeSinceLastSync < mTargetFrameDuration) {
        sleep(mTargetFrameDuration - timeSinceLastSync); // Sleep to maintain target FPS
    }

    mLastSyncTime = getCurrentTime(); // Update last sync time
}
