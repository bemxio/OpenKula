#ifndef STRUCTS_H
#define STRUCTS_H

#if defined(NXDK)
    #include <SDL.h>
    #include <SDL_ttf.h>

    #include "../../mixer/mixer.h"
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

struct Player {
    struct Entity;

    bool jumpCycle;
    Uint8 jumpTimer;
};

struct Enemy {
    struct Entity;

    bool mouthCycle;
    Uint8 mouthTimer;
    Uint32 ghostTimer;
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
    Sint32 score;
    Uint32 scoreTimer;

    Player player;
    Enemy enemy;

    Uint8 controls;
};

typedef struct GameAssets GameAssets;
typedef struct GameState GameState;

#endif