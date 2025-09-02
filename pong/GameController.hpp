#pragma once

#include "Entity.hpp"
#include <list>
#include "Library/AbstractionLayer/PlatformInterface/PlatformInterface.hpp"
#include "ScoreManager.hpp"

class Paddle;
class Ball;

// Possible game states.
enum class GameState {
    RUNNING,
    GAME_OVER,
    UP,
    DOWN,
    STATIONARY,
    START
    // Additional states can be added here...
};


class GameController {
public:
    GameController();
    ~GameController();

    void run();  // this replaces startGame()

private:
    void initializeGame();
    void gameLoop();
    UserInput pollInputBuffer();
    void processInput(UserInput);
    void clampPaddle(Paddle* paddle);
    bool checkCollision(Entity* a, Entity* b);
    void resetBall();
    void HandlePaddleCollision(Ball*, Paddle*, bool);
    void gameOver(int);
    void runInputLoop(GameState);

    PlatformInterface* platformInterface;
    VisualRendererInterface* renderer;
    ClockManagerInterface* clockManager;
    UserInputManagerInterface* userInputManager;
    ResourceManagerInterface* resourceManager;
    AudioRendererInterface* audioRenderer;

    std::list<Entity*>* entities;
    Paddle* paddleLeft;
    Paddle* paddleRight;
    Ball* ball;
    int frameCount;
    int currentFrameRate;
    GameState state;
    ImageInfo* bg;
    ImageInfo* startMsg;
    ImageInfo* scoreBarLeft;
    ImageInfo* scoreBarRight;
    ImageInfo* endMsg;
    ImageInfo* winnerImg;
    ScoreManager* leftScore;
    ScoreManager* rightScore;
    AudioInfo* hitSound;

};
