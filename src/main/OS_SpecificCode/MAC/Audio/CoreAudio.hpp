#pragma once

#include "../../../AbstractionLayer/OtherInterfaces/AudioRendererInterface.hpp"
#include "../../../AbstractionLayer/Util/AudioInfo.hpp"  // Include AudioInfo class
#include <string>
#include <AVFoundation/AVFoundation.h>

class CoreAudio : public AudioRendererInterface {
public:
    CoreAudio();
    ~CoreAudio();
    void playSound(AudioInfo& audio) override;
    void stopAudio() override;
    
private:
    NSMutableArray* mPlayers;
};

