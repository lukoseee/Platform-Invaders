#pragma once

#include <string>
#include "../Util/AudioInfo.hpp"

class AudioRendererInterface {
public:
    virtual void playSound(AudioInfo& audio) = 0;
    virtual void stopAudio() = 0;
    virtual ~AudioRendererInterface() = default;
};

