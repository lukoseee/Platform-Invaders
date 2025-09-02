#pragma once

#include "Util/util.hpp"
#include <string>

// ----------------------------------------------------------------------------
// Constants
// ----------------------------------------------------------------------------

// Window Config
constexpr int NUM_CELLS = 20;
constexpr int CELL_SIZE = 32;
constexpr int WINDOW_WIDTH = NUM_CELLS * CELL_SIZE;
constexpr int WINDOW_HEIGHT = (NUM_CELLS + 2) * CELL_SIZE;
constexpr int FPS = 60;

// Entity Constants
constexpr int FRAME_THRES = FPS / 10;
constexpr float INITAL_SNAKE_LENGTH = 4;

// Game
constexpr Position GAME_INITAL_SNAKE_POS = {5, 5};
constexpr Position GAME_SCORE_POS = {19, 20.5};
constexpr Position GAME_COUNTDOWN_POS = {10, 10};
constexpr int GAME_OVER_HUD_WIDTH = 576;
constexpr int GAME_OVER_HUD_HEIGHT = 288;
constexpr Position GAME_OVER_HUD_POS = {1, 10};
constexpr Position PLAYER_NAME_OFFSET = {1.5, 14.5};
constexpr float PLAYER_NAME_CHAR_GAP = 1.5;
constexpr int PLAYER_NAME_CHAR_LIMIT = 8;
constexpr int GAME_MUSIC_FRAME_THRES = 3300;

// Menu
constexpr Position MENU_INITAL_SNAKE_POS = {1, 1};
constexpr int START_BAR_WIDTH = 10;
constexpr int SCORES_BAR_WIDTH = 12;
constexpr int QUIT_BAR_WIDTH = 8;
constexpr Position START_BAR_POS = {1, 11};
constexpr Position SCORES_BAR_POS = {1, 7};
constexpr Position QUIT_BAR_POS = {1, 3};
constexpr int MENU_MUSIC_FRAME_THRES = 5600;

// Leaderboard
constexpr int NUM_HIGH_SCORES = 5;
constexpr Position LBOARD_NAME_OFFSET = {5, 16};
constexpr Position LBOARD_SCORE_OFFSET = {13, 16};
constexpr int LBOARD_ENTRIES_GAP = 2;
 
// ----------------------------------------------------------------------------
// Asset Paths
// ----------------------------------------------------------------------------

// Audio
constexpr const char* APPLE_COLLECT_SFX = "Collect_SFX";
constexpr const char* DEATH_SFX = "Death_SFX";
constexpr const char*  SELECT_SFX = "Select_SFX";
constexpr const char*  START_SFX = "Start_SFX";
constexpr const char*  MENU_MUSIC = "Menu_Music";
constexpr const char*  GAME_MUSIC = "Game_Music";

// Game
constexpr const char* SNAKE_BODY_UP = "Snake_UP";
constexpr const char* SNAKE_BODY_LEFT = "Snake_LEFT";
constexpr const char* SNAKE_BODY_DOWN = "Snake_DOWN";
constexpr const char* SNAKE_BODY_RIGHT = "Snake_RIGHT";
constexpr const char*  SNAKE_DEATH_PATH_ONE = "Snake_Death_1";
constexpr const char*  SNAKE_DEATH_PATH_TWO = "Snake_Death_2";
constexpr const char*  SNAKE_DEATH_PATH_THREE = "Snake_Death_3";
constexpr const char*  SNAKE_HEAD_UP = "Snake_Head_UP";
constexpr const char*  SNAKE_HEAD_LEFT = "Snake_Head_LEFT";
constexpr const char*  SNAKE_HEAD_DOWN = "Snake_Head_DOWN";
constexpr const char*  SNAKE_HEAD_RIGHT = "Snake_Head_RIGHT";
constexpr const char*  APPLE_PATH = "Apple";

constexpr const char*  BACKGROUND_PATH = "background";
constexpr const char*  SCORE_HEADER_PATH = "score_header";
constexpr const char*  GAME_OVER_HUD = "game_over_hud";

// Menus
constexpr const char*  MENU_SCREEN = "main_menu";
constexpr const char*  QUIT_UNDERLINE_BAR = "quit_bar";
constexpr const char*  SCORES_UNDERLINE_BAR = "scores_bar";
constexpr const char*  START_UNDERLINE_BAR = "start_bar";
constexpr const char*  LBOARD_SCREEN_PATH = "leaderboard_screen";

// Otther
constexpr const char*  SCORES_TXT = "scores";

// Alphanumeric
constexpr const char*  ZERO_PATH = "0";
constexpr const char*  ONE_PATH = "1";
constexpr const char*  TWO_PATH = "2";
constexpr const char*  THREE_PATH = "3";
constexpr const char*  FOUR_PATH = "4";
constexpr const char*  FIVE_PATH = "5";
constexpr const char*  SIX_PATH = "6";
constexpr const char*  SEVEN_PATH = "7";
constexpr const char*  EIGHT_PATH = "8";
constexpr const char*  NINE_PATH = "9";
constexpr const char*  EXCLAMATION_PATH = "exclaim_mark";
constexpr const char*  QUESTION_PATH = "question_mark";
constexpr const char*  COLON_PATH = "colon";
constexpr const char*  A_PATH = "A";
constexpr const char*  B_PATH = "B";
constexpr const char*  C_PATH = "C";
constexpr const char*  D_PATH = "D";
constexpr const char*  E_PATH = "E";
constexpr const char*  F_PATH = "F";
constexpr const char*  G_PATH = "G";
constexpr const char*  H_PATH = "H";
constexpr const char*  I_PATH = "I";
constexpr const char*  J_PATH = "J";
constexpr const char*  K_PATH = "K";
constexpr const char*  L_PATH = "L";
constexpr const char*  M_PATH = "M";
constexpr const char*  N_PATH = "N";
constexpr const char*  O_PATH = "O";
constexpr const char*  P_PATH = "P";
constexpr const char*  Q_PATH = "Q";
constexpr const char*  R_PATH = "R";
constexpr const char*  S_PATH = "S";
constexpr const char*  T_PATH = "T";
constexpr const char*  U_PATH = "U";
constexpr const char*  V_PATH = "V";
constexpr const char*  W_PATH = "W";
constexpr const char*  X_PATH = "X";
constexpr const char*  Y_PATH = "Y";
constexpr const char*  Z_PATH = "Z";


