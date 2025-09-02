#pragma once
#include "../../../AbstractionLayer/OtherInterfaces/ClockManagerInterface.hpp"
#include <windows.h>

class WindowsClockManager : public ClockManagerInterface {
public:
        WindowsClockManager() noexcept;         // Constructor declaration with noexcept
        double getCurrentTime() const override;
        void sleep(double milliseconds) const override;
        void setTargetFrameRate(int fps);       // Declare setTargetFrameRate
        void synchronizeFrame();                // Declare synchronizeFrame
};


