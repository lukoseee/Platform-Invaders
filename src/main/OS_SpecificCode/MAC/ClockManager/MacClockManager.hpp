#pragma once
#include "../../../AbstractionLayer/OtherInterfaces/ClockManagerInterface.hpp"
#include <mach/mach_time.h>

/*
 See ClockManagerInterface for class description
 */
class MacClockManager : public ClockManagerInterface {
public:
    // Constructor declaration with noexcept
    MacClockManager() noexcept;
    
    // Implements frame sync logic
    void synchronizeFrame() override;
    
    void setTargetFrameRate(int fps) override;
    double getCurrentTime() const override;
    void sleep(double milliseconds) const override;
};

