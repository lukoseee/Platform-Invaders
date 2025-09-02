#pragma once

#include "../../../AbstractionLayer/OtherInterfaces/AudioRendererInterface.hpp"
#include "../../../AbstractionLayer/Util/AudioInfo.hpp"

#include <xaudio2.h>
#include <string>
#include <mutex>
#include <unordered_map>

class D2dAudio : public AudioRendererInterface {
private:
    IXAudio2* mXAudio2 = nullptr;
    IXAudio2MasteringVoice* mMasterVoice = nullptr;
    std::unordered_map<IXAudio2SourceVoice*, std::shared_ptr<std::vector<BYTE>>> mActiveVoices;
    std::mutex mAudioMutex;
    bool mIsShuttingDown = false;

public:
    D2dAudio();
    ~D2dAudio();
    void playSound(AudioInfo& audio) override;
    void stopAudio();
};







