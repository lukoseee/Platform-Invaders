#import "CoreAudio.hpp"

CoreAudio::CoreAudio() {
    mPlayers = [[NSMutableArray alloc] init];
}

CoreAudio::~CoreAudio() {
    this->stopAudio(); // Cleanup
}

void CoreAudio::playSound(AudioInfo& audio) {
    // Convert file path from std::string to NSString
    NSString* path = [NSString stringWithUTF8String:audio.getFilePath().c_str()];
    
    // Create a URL object for the file
    NSURL* url = [NSURL fileURLWithPath:path];

    AVPlayer* newPlayer = [AVPlayer playerWithURL:url];
    
    // add player to players and play audio
    if (newPlayer) {
        [newPlayer play];
        [mPlayers addObject:newPlayer];
    }
}

void CoreAudio::stopAudio() {
    for (AVPlayer* player in mPlayers) {
        [player pause];
        [player seekToTime:CMTimeMake(0, 1)];
    }
    [mPlayers removeAllObjects];
}


