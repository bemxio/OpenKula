#ifndef CONSTANTS_H
#define CONSTANTS_H

#define WINDOW_TITLE "Kula 3D"

#define FPS 30
#define GAME_WIDTH 480
#define GAME_HEIGHT 360

#define BACKGROUND_PATH "assets/background.png"
#define BGM_PATH "assets/mortietunes.mp3"
#define ENEMY_CLOSED_PATH "assets/trekant2.png"
#define ENEMY_OPEN_PATH "assets/trekant.png"
#define FONT_PATH "assets/skrifttype.ttf"
#define LOGO_PATH "assets/logo.png"
#define PLAYER_PATH "assets/kula.png"

#define ENEMY_CLONE_INTERVAL 1000
#define ENEMY_GHOST_DURATION 100
#define ENEMY_INITIAL_RECT {401, 281, 46, 61}
#define ENEMY_SPEED 10

#define LOGO_RECT {9, 39, 84, 31}

#define PLAYER_INITIAL_RECT {23, 284, 44, 46}
#define PLAYER_SPEED 10

#define SCORE_POSITION {10, 5}
#define SCORE_COLOR {255, 255, 255}
#define SCORE_SIZE 24
#define SCORE_TEXT "Score: %d"

#endif