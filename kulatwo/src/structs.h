#ifndef STRUCTS_H
#define STRUCTS_H

#if defined(NXDK)
    #include <SDL.h>
    #include <SDL_ttf.h>

    #include "mixer.h"
#else
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_mixer.h>
    #include <SDL2/SDL_ttf.h>
#endif

#include <stdbool.h>
#include <stdint.h>

struct GlideState {
    bool active;

    int32_t startX, startY;
    int32_t targetX, targetY;

    uint32_t startTime;
    uint32_t duration;
};

typedef struct GlideState GlideState;

struct Entity {
    SDL_Rect rect;
    bool active;
    GlideState glideState;
};

struct Paddle {
    struct Entity;
};

struct Ball {
    struct Entity;

    int16_t direction;
    uint32_t paddleTimer;
};

typedef struct Entity Entity;
typedef struct Paddle Paddle;
typedef struct Ball Ball;

struct GameAssets {
    SDL_Texture* background;
    Mix_Music* music;
    TTF_Font* font;

    SDL_Texture* ball;
};

struct GameState {
    int32_t score;

    Paddle paddle;
    Ball ball;

    uint8_t controls;
};

typedef struct GameAssets GameAssets;
typedef struct GameState GameState;

#endif