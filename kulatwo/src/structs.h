#ifndef STRUCTS_H
#define STRUCTS_H

#if defined(NXDK)
    #include <SDL.h>
    #include <SDL_ttf.h>

    #include "../../mixer/mixer.h"
#elif defined(__3DS__)
    #include <SDL.h>
    #include <SDL_mixer.h>
    #include <SDL_ttf.h>
#else
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_mixer.h>
    #include <SDL2/SDL_ttf.h>
#endif

#include <stdbool.h>

struct GlideState {
    bool active;

    Sint32 startX, startY;
    Sint32 targetX, targetY;

    Uint32 startTime;
    Uint32 duration;
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

    Sint16 direction;
    Uint32 paddleTimer;
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
    Sint32 score;

    Paddle paddle;
    Ball ball;

    Uint8 controls;
};

typedef struct GameAssets GameAssets;
typedef struct GameState GameState;

#endif