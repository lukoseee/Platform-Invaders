Notes:
- **These tests are intended for both the Mac and Windows AudioRenderers**
- These tests are highly dependent on the Audio class
- These tests are subject to change based upon the needs of the game developers

# Playing Audio
- [ ] Verify an audio file can be played : given a correctly initalised Audio* object (with a correct filepath), ensure the audio file can be played
- [ ] Verify an Audio* object can only be played once : as above, however subsequent calls to play the audio of the same object should do nothing.

# Stopping Audio
- [ ] Verify an audio file can be stopped : given an already playing audio file 
- [ ] Verify an audio file cannot be stopped if it is not player : calls to stop the audio if the Audio* object is not 'running' should do nothing.