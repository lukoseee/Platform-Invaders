#pragma once

/*
 ClockManagerInterface provides a platform-agnostic mechanism for timing game
 elements.
 
 This allows for the game layer to utilise a framerate cap, ensuring smooth
 and consistent game object updates.
 */
class ClockManagerInterface {
public:
    // get the current time of the system's internal clock
    virtual double getCurrentTime(void) const = 0;
    
    // sleep the current thread, i.e. delay the game
    virtual void sleep(double milliseconds) const = 0;
    
    // delay the game until the target framerate is met. Implementing a
    // framerate cap
    virtual void synchronizeFrame(void) = 0;
    
    virtual void setTargetFrameRate(int fps) = 0;
    virtual ~ClockManagerInterface(void) = default;

protected:
    // frame duration in milliseconds
    double mTargetFrameDuration;
    
    // last time synchronizeFrame() was called
    double mLastSyncTime;
};


