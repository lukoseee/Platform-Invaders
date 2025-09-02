#pragma once

#include "Game/Entity.hpp"

// Window dimensions.
constexpr int WINDOW_WIDTH = 1000;
constexpr int WINDOW_HEIGHT = 800;

// Image identifiers.
constexpr const char* PLAYER_IMAGE = "0_player_sprite";
constexpr const char* ENEMY_IMAGE_FRAME0 = "0_enemy_sprite";
constexpr const char* ENEMY_IMAGE_FRAME1 = "1_enemy_sprite";
constexpr const char* ENEMY_IMAGE_FRAME2 = "3_enemy_sprite";
constexpr const char* ENEMY_IMAGE_FRAME3 = "4_enemy_sprite";
constexpr const char* ENEMY_IMAGE_FRAME4 = "5_enemy_sprite";
constexpr const char* ENEMY_IMAGE_FRAME5 = "6_enemy_sprite";
constexpr const char* RED_ENEMY_IMAGE = "red_enemy";
constexpr const char* BULLET_IMAGE = "0_bullet_sprite";
constexpr const char* BULLET_ENEMY_IMAGE_0 = "2_bullet_sprite";
constexpr const char* BULLET_ENEMY_IMAGE_1 = "4_bullet_sprite";
constexpr const char* LIVES_IMAGE = "lives_text";
constexpr const char* INTRO_BACKGROUND_IMAGE = "main_menu_background";
constexpr const char* GAME_OVER_IMAGE = "game_over_background";
constexpr const char* SCORE_IMAGE = "score_text";
constexpr const char* SCORES_TXT = "scores";
constexpr const char* LBOARD_SCREEN_PATH = "leaderboard_background";
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
constexpr const char* A_PATH = "A";
constexpr const char* B_PATH = "B";
constexpr const char* C_PATH = "C";
constexpr const char* D_PATH = "D";
constexpr const char* E_PATH = "E";
constexpr const char* F_PATH = "F";
constexpr const char* G_PATH = "G";
constexpr const char* H_PATH = "H";
constexpr const char* I_PATH = "I";
constexpr const char* J_PATH = "J";
constexpr const char* K_PATH = "K";
constexpr const char* L_PATH = "L";
constexpr const char* M_PATH = "M";
constexpr const char* N_PATH = "N";
constexpr const char* O_PATH = "O";
constexpr const char* P_PATH = "P";
constexpr const char* Q_PATH = "Q";
constexpr const char* R_PATH = "R";
constexpr const char* S_PATH = "S";
constexpr const char* T_PATH = "T";
constexpr const char* U_PATH = "U";
constexpr const char* V_PATH = "V";
constexpr const char* W_PATH = "W";
constexpr const char* X_PATH = "X";
constexpr const char* Y_PATH = "Y";
constexpr const char* Z_PATH = "Z";

// Sound identifiers.
constexpr const char* SHOOT_SOUND = "shoot";
constexpr const char* ENEMY_EXPLOSION_SOUND = "enemy_explosion";
constexpr const char* GAME_BACKGROUND_MUSIC = "game_background_music"; // To be implemented
constexpr const char* PLAYER_DEATH_SOUND = "player_death";
constexpr const char* RED_ENEMY_SPAWN_SOUND = "red_enemy_spawn";
constexpr const char* SOUND_EFFECT_SOUND = "sound_effect";

// Shield dimensions.
constexpr int SHIELD_IMAGE_WIDTH = 20;
constexpr int SHIELD_IMAGE_HEIGHT = 20;
constexpr int SHIELD_INITIAL_HEALTH = 4;
// Shield positions for blocks.
constexpr int SHIELD1_X = 100;
constexpr int SHIELD1_Y = 150;
constexpr int SHIELD2_X = 300;
constexpr int SHIELD2_Y = 150;
constexpr int SHIELD3_X = 500;
constexpr int SHIELD3_Y = 150;
constexpr int SHIELD4_X = 700;
constexpr int SHIELD4_Y = 150;

// Player dimensions and settings.
constexpr int PLAYER_START_X = 100;
constexpr int PLAYER_START_Y = 50;
constexpr int PLAYER_INITIAL_HEALTH = 1;
constexpr int PLAYER_WIDTH = 50;
constexpr int PLAYER_HEIGHT = 50;
constexpr int PLAYER_DEATH_WIDTH = 50;
constexpr int PLAYER_DEATH_HEIGHT = 50;
constexpr int PLAYER_DEATH_DURATION = 120; // 2 seconds at 60 FPS.
constexpr int PLAYER_DEATH_ANIMATION_THRESHOLD = 15; // Frames between animation toggles.
constexpr int PLAYER_MOVE_DISTANCE = 10;
constexpr int PLAYER_SHOOT_COOLDOWN = 25; // Frames.

// Bullet dimensions and speeds.
constexpr int BULLET_WIDTH = 5;
constexpr int BULLET_HEIGHT = 10;
constexpr int BULLET_ENEMY_WIDTH = 15;
constexpr int BULLET_ENEMY_HEIGHT = 20;
constexpr int BULLET_ANIMATION_THRESHOLD = 10; // Frames between animation toggles.
constexpr int BULLET_PLAYER_SPEED = 5;
constexpr int BULLET_ENEMY_SPEED = 5;
constexpr int BULLET_OFFSET_X = 22;
constexpr int BULLET_OFFSET_Y = 40;

// Enemy settings.
constexpr int ENEMY_WIDTH = 30;
constexpr int ENEMY_HEIGHT = 30;
//constexpr int ENEMY_GROUP_SPEED = 1;
constexpr int ENEMY_GROUP_SPEED = 1;
constexpr int ENEMY_ANIMATION_THRESHOLD = 60; // Frames between animation toggles.
constexpr int ENEMY_SHOOT_COOLDOWN_INITIAL = 150;
constexpr int ENEMY_SHOOT_COOLDOWN_MIN = 200;
constexpr int ENEMY_SHOOT_COOLDOWN_RANGE = 1500;
constexpr int ENEMY_EXPLOSION_DURATION = 10; // Frames for explosion animation.
constexpr int ENEMY_DESCENT_AMOUNT = 10; // Pixels to move down when hitting edge.
constexpr int ENEMY_SPEED_INCREMENT_PER_WAVE = 1; // Increase enemy speed each wave.

// Enemy movement sound identifiers.
constexpr const char* ENEMY_MOVE_SOUNDS[] = {"1", "2", "3", "4"};
constexpr int NUM_ENEMY_MOVE_SOUNDS = 4;

// RedEnemy settings.
constexpr int RED_ENEMY_WIDTH = 30;
constexpr int RED_ENEMY_HEIGHT = 30;
constexpr int RED_ENEMY_SPAWN_X = -150;
constexpr int RED_ENEMY_Y = 750;
constexpr int RED_ENEMY_SPEED = 2;
constexpr int RED_ENEMY_MARGIN = 50;
constexpr int RED_ENEMY_EXPLOSION_DURATION = 10; // Frames for explosion animation.
constexpr int RED_ENEMY_SPAWN_INTERVAL = 1220;

// Score system constants.
constexpr int NORMAL_ENEMY_SCORE = 10;
constexpr int RED_ENEMY_SCORE_VALUES[6] = {50, 100, 150, 200, 250, 300};
constexpr int RED_ENEMY_SCORE_VALUES_SIZE = 6;

// Lives settings.
constexpr int PLAYER_INITIAL_LIVES = 3;
constexpr int LIVES_ICON_WIDTH = 30;
constexpr int LIVES_ICON_HEIGHT = 20;
constexpr int LIVES_DISPLAY_X = WINDOW_WIDTH - 310; // Top-right.
constexpr int LIVES_DISPLAY_Y = 20;
constexpr int LIVES_TEXT_IMAGE_WIDTH = 100;
constexpr int LIVES_TEXT_IMAGE_HEIGHT = 20;
constexpr int LIFE_ICON_OFFSET_X = 20;
constexpr int LIFE_ICON_SPACING = 40;

// Enemy formation settings.
constexpr int ENEMY_ROWS = 5;
constexpr int ENEMY_PER_ROW = 11;
constexpr int ENEMY_INITIAL_X = 100;
constexpr int ENEMY_INITIAL_Y = 500;
constexpr int ENEMY_ROW_SPACING = 50;
constexpr int ENEMY_COLUMN_SPACING = 50;

// Game mechanics.
constexpr int SPEED_UP_INTERVAL = 120;
constexpr int GAME_OVER_ENEMY_Y_THRESHOLD = 200;
constexpr int MAX_FRAME_RATE = 75;
constexpr int FPS = 60;

// Shield block layout settings.
constexpr int SHIELD_BLOCK_ROWS = 3;
constexpr int SHIELD_BLOCK_COLS = 4;

// Arrow pointer settings.
constexpr int ARROW_X = 50;
constexpr int START_GAME_Y = 300;
constexpr int LEADERBOARD_Y = 360;
constexpr int QUIT_Y = 420;
constexpr const char* ARROW_IMAGE= "arrow";
constexpr int ARROW_W = 50;
constexpr int ARROW_H= 50;

// Music settings.
constexpr int INITIAL_MUSIC_FRAME_THRESHOLD      = 60;  
constexpr int MUSIC_THRESHOLD_DECREMENT_PER_WAVE = 2;   
constexpr int MIN_MUSIC_FRAME_THRESHOLD          = 40;  

// Name entry settings
constexpr int PLAYER_NAME_CHAR_LIMIT = 12;
constexpr int PLAYER_NAME_CHAR_GAP = 36;
constexpr int NAME_ENTRY_X = 290;
constexpr int NAME_ENTRY_Y = 405;
constexpr int SCORE_VALUE_X = 640;  // X position right of "SCORE" text
constexpr int SCORE_VALUE_Y = 280;  // Y position matching "SCORE" text
constexpr int DIGIT_SPACING = 30;   // Space between score digits

// Leaderboard
constexpr int NUM_HIGH_SCORES = 5;
constexpr int LBOARD_CHAR_SIZE = 32;
constexpr int LBOARD_NAME_OFFSET_X = 128;
constexpr int LBOARD_NAME_OFFSET_Y = 592;
constexpr int LBOARD_SCORE_OFFSET_X = LBOARD_NAME_OFFSET_X + ((PLAYER_NAME_CHAR_LIMIT + 2) * LBOARD_CHAR_SIZE);
constexpr int LBOARD_SCORE_OFFSET_Y = LBOARD_NAME_OFFSET_Y;
constexpr int LBOARD_ENTRIES_GAP = 2;

// Wave settings
constexpr int INITIAL_WAVE_COUNT = 1;
