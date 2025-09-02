#pragma once
#include <string>
#include "Entity.hpp"

constexpr int WINDOW_WIDTH = 1000;
constexpr int WINDOW_HEIGHT = 700;
constexpr int SCORE_HEADER_HEIGHT = 47;
constexpr int SCORE_HEADER_WIDTH = 341;

constexpr int FPS = 60;

constexpr float BALL_SPEED_X = 7.0f;
constexpr float BALL_SPEED_Y = 7.0f;

constexpr float PADDLE1_POS_X = 30.0f;
constexpr float PADDLE1_POS_Y = WINDOW_HEIGHT / 2.0f;
constexpr int PADDLE_SIZE_X = 17;
constexpr int PADDLE_SIZE_Y = 110;
constexpr float BALL_POS = WINDOW_WIDTH / 2.0f;
constexpr int BALL_SIZE = 25;
constexpr int START_MSG_POS = 185;
constexpr int END_MSG_POS = 195;
constexpr int WINNER_MSG_POS = 390;
		
constexpr float PADDLE2_POS_X = WINDOW_WIDTH - 50.0f;
constexpr float PADDLE2_POS_Y = WINDOW_HEIGHT / 2.0f;
constexpr float PADDLE_SPEED = 12.0f;

constexpr float LEFT_PLAYER_SCORE_POS_X = 250;
constexpr float SCORE_POS_Y = WINDOW_HEIGHT - 40;
constexpr float RIGHT_PLAYER_SCORE_POS_X = WINDOW_WIDTH - 250;
constexpr float SCORE_SIZE = 35;
constexpr float BOARD_BOUNDARY_Y = WINDOW_HEIGHT - SCORE_HEADER_HEIGHT;
constexpr int POINTS_LIMIT = 11;
constexpr int WINMSG_SIZE_X = 240;
constexpr int WINMSG_SIZE_Y = 50;

constexpr const char* PADDLE1 = "Computer";
constexpr const char* SCORE_BAR_LEFT = "ScoreBar";
constexpr const char* SCORE_BAR_RIGHT = "ScoreBarRight";
constexpr const char* PADDLE2 = "Player";
constexpr const char* BALL = "Ball";
constexpr const char* BG = "Board";
constexpr const char* STARTMSG = "StartMessage";
constexpr const char* ZERO_PATH = "0";
constexpr const char* ONE_PATH = "1";
constexpr const char* TWO_PATH = "2";
constexpr const char* THREE_PATH = "3";
constexpr const char* FOUR_PATH = "4";
constexpr const char* FIVE_PATH = "5";
constexpr const char* SIX_PATH = "6";
constexpr const char* SEVEN_PATH = "7";
constexpr const char* EIGHT_PATH = "8";
constexpr const char* NINE_PATH = "9";
constexpr const char* PLAYER1WINS = "Player1Wins";
constexpr const char* PLAYER2WINS = "Player2Wins";
constexpr const char* END_MSG = "EndMsg";
constexpr const char* HIT_SOUND = "hit";
constexpr int MSG_SIZE_X = 600;
constexpr int MSG_SIZE_Y = 45;

constexpr float MAX_BOUNCE_ANGLE = 45.0f * (3.14159f / 180.0f);
constexpr float BALL_ACCELERATION = 1.1f;

// Player settings
constexpr int PLAYER1 = 1;
constexpr int PLAYER2 = 2;

// Game states
constexpr int POSITIION_OFFSET = 40;

// Normalization constants
constexpr float HITPOS_SCALE = 2.0f;
constexpr float HITPOS_OFFSET = 1.0f;
