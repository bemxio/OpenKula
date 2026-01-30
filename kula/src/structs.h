#ifndef STRUCTS_H
#define STRUCTS_H

#if defined(NXDK)
    #include <SDL.h>
    #include <SDL_ttf.h>

    #include "audio.h"
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

struct Player {
    struct Entity;

    bool jumpCycle;
    uint8_t jumpTimer;
};

struct Enemy {
    struct Entity;

    bool mouthCycle;
    uint8_t mouthTimer;
    uint32_t ghostTimer;
};

typedef struct Entity Entity;
typedef struct Player Player;
typedef struct Enemy Enemy;

struct GameAssets {
    SDL_Texture* background;
    Mix_Music* music;
    TTF_Font* font;

    SDL_Texture* player;
    SDL_Texture* enemyOpen;
    SDL_Texture* enemyClosed;
};

struct GameState {
    int32_t score;
    uint32_t scoreTimer;

    Player player;
    Enemy enemy;

    uint8_t controls;
};

typedef struct GameAssets GameAssets;
typedef struct GameState GameState;

#endif