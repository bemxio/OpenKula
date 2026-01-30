#ifndef CONSTANTS_H
#define CONSTANTS_H

#define WINDOW_TITLE "Kula"

#define FPS 30
#define GAME_WIDTH 480
#define GAME_HEIGHT 360

#if defined(__PS2__)
    #define BACKGROUND_PATH "cdrom0:/kulabakgrunn.png"
    #define BGM_PATH "cdrom0:/mortietunes.mp3"
    #define ENEMY_CLOSED_PATH "cdrom0:/fiende02.png"
    #define ENEMY_OPEN_PATH "cdrom0:/fiende01.png"
    #define FONT_PATH "cdrom0:/skrifttype.ttf"
    #define PLAYER_PATH "cdrom0:/kula.png"
#elif defined(NXDK)
    #define BACKGROUND_PATH "D:\\assets\\kulabakgrunn.png"
    #define BGM_PATH "D:\\assets\\mortietunes.mp3"
    #define ENEMY_CLOSED_PATH "D:\\assets\\fiende02.png"
    #define ENEMY_OPEN_PATH "D:\\assets\\fiende01.png"
    #define FONT_PATH "D:\\assets\\skrifttype.ttf"
    #define PLAYER_PATH "D:\\assets\\kula.png"
#else
    #define BACKGROUND_PATH "assets/kulabakgrunn.png"
    #define BGM_PATH "assets/mortietunes.mp3"
    #define ENEMY_CLOSED_PATH "assets/fiende02.png"
    #define ENEMY_OPEN_PATH "assets/fiende01.png"
    #define FONT_PATH "assets/skrifttype.ttf"
    #define PLAYER_PATH "assets/kula.png"
#endif

#define ENEMY_ANIMATION_DELAY 10
#define ENEMY_GLIDE_DURATION 2000
#define ENEMY_GHOST_DURATION 100
#define ENEMY_INITIAL_RECT {447, 294, 48, 53}

#define PLAYER_GLIDE_DURATION 1000
#define PLAYER_INITIAL_RECT {41, 308, 37, 34}
#define PLAYER_SPEED 10

#define SCORE_COLOR {255, 255, 255}
#define SCORE_RECT {10, 5, 0, 0}
#define SCORE_SIZE 24
#define SCORE_TEXT "score: %d"

#endif