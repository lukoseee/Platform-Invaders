#include "MacClockManager.hpp"
#import <Foundation/Foundation.h>
#include <mach/mach_time.h>

MacClockManager::MacClockManager() noexcept {
    mTargetFrameDuration = 0;
    mLastSyncTime = 0;
}

double MacClockManager::getCurrentTime() const {
    // get timebase infomation using mach_time.h
    static mach_timebase_info_data_t timebase;
    if (timebase.denom == 0) {
        mach_timebase_info(&timebase);
    }
    
    // get the current time
    uint64_t time = mach_absolute_time();
    
    // Convert time using timebase and return it in milliseconds
    return (time * timebase.numer / timebase.denom) / 1e6;
}

void MacClockManager::sleep(double milliseconds) const {
    // sleep the thread for the given ms
    [NSThread sleepForTimeInterval:milliseconds / 1000.0];
}

void MacClockManager::setTargetFrameRate(int fps) {
    mTargetFrameDuration = 1000.0 / fps; // Set frame duration in milliseconds
}

void MacClockManager::synchronizeFrame() {
    double currentTime = getCurrentTime();
    double timeSinceLastSync = currentTime - mLastSyncTime;

    // if the time since the last sync has occured is less than the desired
    // frame duration length
    if (timeSinceLastSync < mTargetFrameDuration) {
        // Sleep to maintain target FPS
        sleep(mTargetFrameDuration - timeSinceLastSync);
    }

    // store the time which the last sync happened, i.e. 'now'
    mLastSyncTime = getCurrentTime();
}
