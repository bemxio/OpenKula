#ifndef CONSTANTS_H
#define CONSTANTS_H

#define WINDOW_TITLE "Kula 2"

#define FPS 30
#define GAME_WIDTH 480
#define GAME_HEIGHT 360

#define BACKGROUND_PATH "assets/blue_sky.svg"
#define BALL_PATH "assets/drakt1.svg"
#define FONT_PATH "assets/skrifttype.ttf"
#define MUSIC_PATH "assets/mortietunes.mp3"

#define PADDLE_COLOR 255, 230, 0, 255
#define PADDLE_INITIAL_RECT {4, 324, 89, 15}
#define PADDLE_SPEED 15

#define BALL_INITIAL_DIRECTION 45
#define BALL_INITIAL_RECT {318, 303, 39, 38}
#define BALL_SPEED 15

#define BARRIER_COLOR 255, 0, 0, 255
#define BARRIER_RECT {-4, 349, 484, 13}

#define SCORE_COLOR {255, 255, 255}
#define SCORE_RECT {10, 5, 0, 0}
#define SCORE_SIZE 24
#define SCORE_TEXT "score: %d"

#endif