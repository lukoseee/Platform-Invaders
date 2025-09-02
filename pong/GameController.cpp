
#include "GameController.hpp"
#include "Paddle.hpp"
#include "constants.hpp"
#include "Ball.hpp"
#include <iostream>


GameController::GameController()
{
    platformInterface = new PlatformInterface();
    renderer = platformInterface->getVisualRenderer();
    clockManager = platformInterface->getClockManager();
    userInputManager = platformInterface->getUserInputManager();
    resourceManager = platformInterface->getResourceManager();
    audioRenderer = platformInterface->getAudioRenderer();
    leftScore = new ScoreManager(renderer, resourceManager);
    rightScore = new ScoreManager(renderer, resourceManager);

    entities = new std::list<Entity*>();
    
    frameCount = 0;

    paddleLeft = nullptr;
    paddleRight = nullptr;
    ball = nullptr;
    bg = nullptr;
    startMsg = nullptr;
    endMsg = nullptr;
    winnerImg = nullptr;
    scoreBarLeft = nullptr;
    scoreBarRight = nullptr;

    currentFrameRate = FPS;

    state = GameState::START;

}

GameController::~GameController()
{
	for (Entity* entity : *entities) {
		delete entity;
	}
    delete bg;
	delete entities;
	delete platformInterface;
    delete renderer;
    delete clockManager;
    delete userInputManager;
    delete resourceManager;
    delete startMsg;
    delete scoreBarLeft;
    delete scoreBarRight;
    delete leftScore;
    delete rightScore;
    delete winnerImg;
    delete endMsg;
    delete hitSound;
    delete audioRenderer;
}

UserInput GameController::pollInputBuffer()
{

    if (userInputManager->isEmpty()) {
        return UNDEFINED;
    }
	UserInput input = userInputManager->getNextInput();


    return input;
}

void GameController::run()
{
    initializeGame();
}

void GameController::initializeGame()
{   

	printf("Initializing game...\n");
  
    renderer->createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Pong", false);
    clockManager->setTargetFrameRate(FPS);

    paddleLeft = new Paddle(PADDLE1_POS_X, PADDLE1_POS_Y, PADDLE_SPEED);
    paddleRight = new Paddle(PADDLE2_POS_X, PADDLE2_POS_Y, PADDLE_SPEED);

	printf("Paddles created.\n");

    paddleLeft->setImage(resourceManager->makeImage(PADDLE1, PADDLE_SIZE_X, PADDLE_SIZE_Y, true));
    paddleRight->setImage(resourceManager->makeImage(PADDLE2, PADDLE_SIZE_X, PADDLE_SIZE_Y, true));

    bg = resourceManager->makeImage(BG, WINDOW_WIDTH, WINDOW_HEIGHT , true);
    startMsg = resourceManager->makeImage(STARTMSG, MSG_SIZE_X, MSG_SIZE_Y, true);
    scoreBarLeft = resourceManager->makeImage(SCORE_BAR_LEFT, SCORE_HEADER_WIDTH, SCORE_HEADER_HEIGHT , true);
    scoreBarRight = resourceManager->makeImage(SCORE_BAR_RIGHT, SCORE_HEADER_WIDTH, SCORE_HEADER_HEIGHT, true);

	printf("Paddle images set.\n");

    entities->push_back(paddleLeft);
    entities->push_back(paddleRight);

    renderer->renderImage(bg, 0, 0 - SCORE_HEADER_HEIGHT);
	renderer->renderImage(paddleLeft->getImage(), paddleLeft->getPosition().x, paddleLeft->getPosition().y);
	renderer->renderImage(paddleRight->getImage(), paddleRight->getPosition().x, paddleRight->getPosition().y);

    ball = new Ball(BALL_POS, BALL_POS);

    ball->setVelocity({ -BALL_SPEED_X, BALL_SPEED_Y });
    ball->setImage(resourceManager->makeImage(BALL, BALL_SIZE, BALL_SIZE, true));

	renderer->renderImage(ball->getImage(), ball->getPosition().x, ball->getPosition().y);
    
    renderer->renderImage(startMsg, START_MSG_POS, WINDOW_HEIGHT/2);
    renderer->renderImage(scoreBarLeft, 0, WINDOW_HEIGHT - SCORE_HEADER_HEIGHT);
    renderer->renderImage(scoreBarRight, WINDOW_WIDTH - SCORE_HEADER_WIDTH, WINDOW_HEIGHT - SCORE_HEADER_HEIGHT);

    hitSound = resourceManager->makeAudio(HIT_SOUND);
    
    entities->push_back(ball);

	printf("Game initialized.\n");

    runInputLoop(GameState::START);

    leftScore->initalise(LEFT_PLAYER_SCORE_POS_X, SCORE_POS_Y);
    rightScore->initalise(RIGHT_PLAYER_SCORE_POS_X, SCORE_POS_Y);
    
    

    renderer->removeImage(startMsg);

    gameLoop();

}

void GameController::gameOver(int player)
{   
    endMsg = resourceManager->makeImage(END_MSG, MSG_SIZE_X, MSG_SIZE_Y , true);

    if (player == PLAYER1){
        winnerImg = resourceManager->makeImage(PLAYER1WINS, WINMSG_SIZE_X, WINMSG_SIZE_Y, true);
    }
    else if (player == PLAYER2){
        winnerImg = resourceManager->makeImage(PLAYER2WINS, WINMSG_SIZE_X, WINMSG_SIZE_Y, true);
    }

    renderer->renderImage(endMsg, END_MSG_POS, WINDOW_HEIGHT / 2 - POSITIION_OFFSET);

    renderer->renderImage(winnerImg, WINNER_MSG_POS, WINDOW_HEIGHT / 2);

    runInputLoop(GameState::GAME_OVER);

    renderer->removeImage(winnerImg);
    renderer->removeImage(endMsg);

    leftScore->setScore(0);
    rightScore->setScore(0);

    gameLoop();
}

void GameController::runInputLoop(GameState s) {

    while (state == s)
    {
        while (!userInputManager->isEmpty()) {
            UserInput input = pollInputBuffer();
            processInput(input);
        }
        renderer->updateDisplay();
    }

}

void GameController::gameLoop()
{

    while (state == GameState::RUNNING) {

        // process all user inputs.
        while (!userInputManager->isEmpty()) {
            UserInput input = pollInputBuffer();
            processInput(input);
        }

        // update ball position
        ball->update();

        paddleLeft->update(); paddleRight->update();

        //Clamp paddle positions
        clampPaddle(paddleLeft);
        clampPaddle(paddleRight);

        // ball collision with top/bottom walls
        Position ballPos = ball->getPosition();

		if (ballPos.y <= 0 || ballPos.y + ball->getImage()->getHeight() >= BOARD_BOUNDARY_Y) { //account for window border
            ball->bounceVertical();
            audioRenderer->playSound(*hitSound);
        }

        // ball collision with paddles
        if (checkCollision(ball, paddleLeft) ) {

            HandlePaddleCollision(ball, paddleLeft, true);
            audioRenderer->playSound(*hitSound);

        }
        else if (checkCollision(ball, paddleRight))
        {
            HandlePaddleCollision(ball, paddleRight, false);
            audioRenderer->playSound(*hitSound);
        }

        // ball out of bounds
        if (ballPos.x < 0 ) {
            resetBall();
            rightScore->incScore();
        }
        else if (ballPos.x > WINDOW_WIDTH)
        {
            resetBall();
            leftScore->incScore();
        }

        if (rightScore->getScore() >= POINTS_LIMIT)
        {   
            state = GameState::GAME_OVER;
            gameOver(1);
        }
        else if (leftScore->getScore() >= POINTS_LIMIT)
        {
            state = GameState::GAME_OVER;
            gameOver(2);
        }

        // render everything
        for (Entity* entity : *entities) {
            entity->render(renderer);
        }

        renderer->updateDisplay();
		
        platformInterface->getClockManager()->synchronizeFrame();
    }
}

void GameController::processInput(UserInput input)
{
    
    switch (input) {
        case W_DOWN: paddleLeft->setState(GameState::UP); break;
        case S_DOWN: paddleLeft->setState(GameState::DOWN); break;
        case UP_ARROW_DOWN: paddleRight->setState(GameState::UP); break;
        case DOWN_ARROW_DOWN: paddleRight->setState(GameState::DOWN); break;
        case RETURN_DOWN: state = GameState::RUNNING; break;
        default: paddleLeft->setState(GameState::STATIONARY); paddleRight->setState(GameState::STATIONARY); break;
    }
}

void GameController::clampPaddle(Paddle* paddle) {
    Position pos = paddle->getPosition();
    pos.y = std::max(0.0f, std::min(pos.y, static_cast<float>(BOARD_BOUNDARY_Y - paddle->getImage()->getHeight())));
    paddle->setPosition(pos);
}

bool GameController::checkCollision(Entity* a, Entity* b) {
 
    Position posA = a->getPosition();
    Position posB = b->getPosition();

    float ax = posA.x;
    float ay = posA.y;
    int aw = a->getImage()->getWidth();
    int ah = a->getImage()->getHeight();

    float bx = posB.x;
    float by = posB.y;
    int bw = b->getImage()->getWidth();
    int bh = b->getImage()->getHeight();

    bool xOverlap = ax <= bx + bw && ax + aw >= bx;
    bool yOverlap = ay <= by + bh && ay + ah >= by;

    return xOverlap && yOverlap;

}

void GameController::resetBall() {

    ball->setPosition({ BALL_POS, BALL_POS });
    ball->setVelocity({ (rand() % 2 == 0 ? 1.0f : -1.0f) * BALL_SPEED_X, BALL_SPEED_Y });
}

void GameController::HandlePaddleCollision(Ball* ball, Paddle* paddle, bool isLeft)
{   

    Position ballPos = ball->getPosition();
    Position paddleLeftPos = paddle->getPosition();

    float hitPos = (ballPos.y + ball->getImage()->getHeight() / 2.0f - paddleLeftPos.y) / PADDLE_SIZE_Y;

    //normalise hitpos
    hitPos = hitPos * HITPOS_SCALE - HITPOS_OFFSET;

    float reflectionAngle = hitPos * MAX_BOUNCE_ANGLE;

    float speed = std::sqrt((ball->getVelocity().x * ball->getVelocity().x) + (ball->getVelocity().y * ball->getVelocity().y));

    float velocityY = speed * std::sin(reflectionAngle);
    float velocityX = std::abs(ball->getVelocity().x);

    if (isLeft)
    {   
        Position pos = { velocityX * BALL_ACCELERATION, velocityY * BALL_ACCELERATION };
        ball->setVelocity(pos);
    }
    else {

        Position pos = { -velocityX * BALL_ACCELERATION, velocityY * BALL_ACCELERATION };
        ball->setVelocity(pos);
    }

}