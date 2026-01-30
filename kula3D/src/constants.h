#ifndef CONSTANTS_H
#define CONSTANTS_H

#define WINDOW_TITLE "Kula 3D"

#define FPS 30
#define GAME_WIDTH 480
#define GAME_HEIGHT 360

#if defined(NXDK)
    #define BACKGROUND_PATH "D:\\assets\\background.png"
    #define BGM_PATH "D:\\assets\\mortietunes.mp3"
    #define ENEMY_CLOSED_PATH "D:\\assets\\trekant2.png"
    #define ENEMY_OPEN_PATH "D:\\assets\\trekant.png"
    #define FONT_PATH "D:\\assets\\skrifttype.ttf"
    #define LOGO_PATH "D:\\assets\\logo.png"
    #define PLAYER_PATH "D:\\assets\\kula.png"
#else
    #define BACKGROUND_PATH "assets/background.png"
    #define BGM_PATH "assets/mortietunes.mp3"
    #define ENEMY_CLOSED_PATH "assets/trekant2.png"
    #define ENEMY_OPEN_PATH "assets/trekant.png"
    #define FONT_PATH "assets/skrifttype.ttf"
    #define LOGO_PATH "assets/logo.png"
    #define PLAYER_PATH "assets/kula.png"
#endif

#define FONT_INITIAL_SIZE 64

#define PLAYER_INITIAL_RECT {23, 284, 44, 46}
#define PLAYER_SPEED 10

#define ENEMY_CLONE_AMOUNT 2
#define ENEMY_CLONE_INTERVAL 1000
#define ENEMY_GHOST_DURATION 100
#define ENEMY_INITIAL_RECT {401, 281, 46, 61}
#define ENEMY_SPEED 10

#define SCORE_COLOR {255, 255, 255}
#define SCORE_RECT {10, 5, 0, 0}
#define SCORE_SIZE 24
#define SCORE_TEXT "Score: %d"

#define LOGO_RECT {9, 39, 84, 31}

#define GAME_OVER_CAPTION_SIZE 64
#define GAME_OVER_CAPTION_TEXT "Game Over"
#define GAME_OVER_COLOR {255, 0, 0}
#define GAME_OVER_SPACING 25
#define GAME_OVER_SUBCAPTION_SIZE 32

#if defined(__wii__)
    #define GAME_OVER_SUBCAPTION_TEXT "Press the + button to restart"
#elif defined(__vita__)
    #define GAME_OVER_SUBCAPTION_TEXT "Press the Start button to restart"
#else
    #define GAME_OVER_SUBCAPTION_TEXT "Press the Enter key to restart"
#endif

#endif