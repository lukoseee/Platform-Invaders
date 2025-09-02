#include "D2dAudio.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <chrono>

// Link against XAudio2.lib
#pragma comment(lib, "xaudio2.lib")

D2dAudio::D2dAudio() {
    HRESULT hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    if (hr == RPC_E_CHANGED_MODE) {
        std::cerr << "Warning: COM was already initialized with a different mode.\n";
    }
    if (FAILED(hr)) {
        std::cerr << "Failed to initialize COM.\n";
        return;
    }

    hr = XAudio2Create(&mXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
    if (FAILED(hr)) {
        std::cerr << "Failed to initialize XAudio2 engine.\n";
        return;
    }

    hr = mXAudio2->CreateMasteringVoice(&mMasterVoice);
    if (FAILED(hr)) {
        std::cerr << "Failed to create mastering voice.\n";
        mXAudio2->Release();
        mXAudio2 = nullptr;
    }
}

D2dAudio::~D2dAudio() {
    stopAudio();
    if (mMasterVoice) mMasterVoice->DestroyVoice();
    if (mXAudio2) mXAudio2->Release();
}

void D2dAudio::playSound(AudioInfo& audio) {
    std::lock_guard<std::mutex> lock(mAudioMutex);

    std::string filePath = audio.getFilePath();
    std::ifstream file(filePath, std::ios::binary | std::ios::ate);
    if (!file) {
        std::cerr << "Failed to open WAV file: " << filePath << std::endl;
        return;
    }

    size_t fileSize = file.tellg();
    file.seekg(0, std::ios::beg);
    auto audioData = std::make_shared<std::vector<BYTE>>(fileSize);
    file.read(reinterpret_cast<char*>(audioData->data()), fileSize);
    file.close();

    WAVEFORMATEX waveFormat = {};
    waveFormat.wFormatTag = WAVE_FORMAT_PCM;
    waveFormat.nChannels = 2;
    waveFormat.nSamplesPerSec = 44100;
    waveFormat.wBitsPerSample = 16;
    waveFormat.nBlockAlign = (waveFormat.nChannels * waveFormat.wBitsPerSample) / 8;
    waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;

    IXAudio2SourceVoice* newVoice = nullptr;
    HRESULT hr = mXAudio2->CreateSourceVoice(&newVoice, &waveFormat);

    if (FAILED(hr)) {
        std::cerr << "Failed to create source voice. HRESULT: " << std::hex << hr << std::endl;
        return;
    }

    XAUDIO2_BUFFER buffer = {};
    buffer.AudioBytes = static_cast<UINT32>(fileSize - 44);
    buffer.pAudioData = audioData->data() + 44;  // Skip WAV header
    buffer.Flags = XAUDIO2_END_OF_STREAM;

    hr = newVoice->SubmitSourceBuffer(&buffer);
    if (FAILED(hr)) {
        std::cerr << "Failed to submit audio buffer. HRESULT: " << std::hex << hr << std::endl;
        newVoice->DestroyVoice();
        return;
    }

    hr = newVoice->Start(0);
    if (FAILED(hr)) {
        std::cerr << "Failed to start audio playback. HRESULT: " << std::hex << hr << std::endl;
        newVoice->DestroyVoice();
        return;
    }

    // Store voice in map
    mActiveVoices[newVoice] = audioData;

    // Cleanup thread
    std::thread([this, newVoice]() {
        if (!newVoice) return; //safeguard
        XAUDIO2_VOICE_STATE state;
        do {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            std::lock_guard<std::mutex> lock(mAudioMutex);
            if (mIsShuttingDown || !newVoice || mActiveVoices.find(newVoice) == mActiveVoices.end())
                return;
            newVoice->GetState(&state);
        } while (state.BuffersQueued > 0);

        std::lock_guard<std::mutex> lock(mAudioMutex);
        if (newVoice && !mIsShuttingDown) {
            newVoice->Stop(0);
            newVoice->FlushSourceBuffers();
            newVoice->DestroyVoice();
            mActiveVoices.erase(newVoice);
        }
        }).detach();
}

void D2dAudio::stopAudio() {
    std::lock_guard<std::mutex> lock(mAudioMutex);
    mIsShuttingDown = true;

    for (auto& pair : mActiveVoices) {
        pair.first->Stop(0);
        pair.first->FlushSourceBuffers();
        pair.first->DestroyVoice();
    }

    mActiveVoices.clear();

    mIsShuttingDown = false; 
}















