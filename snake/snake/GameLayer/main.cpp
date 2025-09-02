/*
 A simple snake game as been produced. The following notable features are included:
 - Menu GUIs
 - Functional leaderboard with the ability for player(s) to save their scores
 - Music and SFXs
 
 The aim of the game produced is to hightlight the versatility of the Space
 Invaders Library, and to demonstrate the requirements have been met:
 not just Space Invaders can be produced, but also other basic 2D games.
 
 Assets not listed below are of our own making.
 - Alphanumeric assets:
     https://opengameart.org/content/boxy-bold-truetype-font by Clint Bellanger
     under copyright CC0
 - Music:
    https://opengameart.org/content/8-bit-music-pack-1 by MrJoshuaMcLean
    under copyright CC BY-SA 4.0
 - SFX:
 https://opengameart.org/content/retro-game-sound-effects by Vircon32
    under copright CC-BY 4.0
 */

/*
 Note to team library files changed during the development of snake:
 - UserInputManagerInterface.hpp : for DELETE enum
 - MacUserInputManager.cpp and InputView.cpp as per the above
 - AudioRendererInterface.hpp : for stopAudio() which wasnt in there?
 - CoreAudio.hpp and CoreAduio.mm : for better stopping of audio which would somtimes 'miss'
    stopAudio() now stops all playing audio elements
 
 Some of these changes may already be resolved in the latest version of the library, I can't
 remember which branch I got the lib from but clearly it wasnt the most up-to-date one.
 Anyway, these changes should be reviewed (if they aren't fixed in the latest version of
 the library already) and implemented.
 */

#include "controller.hpp"

int main() {
    Controller* controller = new Controller();
    controller->loop();
    delete controller;
    return 0;
}
