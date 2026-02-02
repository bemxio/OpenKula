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
#include <stdint.h>

#include "constants.h"

struct Entity {
    SDL_Rect rect;
    bool active;
    bool hidden;
};

struct Player {
    struct Entity;

    bool jumpCycle;
    uint8_t jumpTimer;
};

struct Enemy {
    struct Entity;

    uint32_t ghostTimer;
    uint32_t cloneTimer;
};

typedef struct Entity Entity;
typedef struct Player Player;
typedef struct Enemy Enemy;

struct GameAssets {
    SDL_Texture* background;
    SDL_Texture* logo;
    Mix_Music* music;
    TTF_Font* font;

    SDL_Texture* player;
    SDL_Texture* enemyOpen;
    SDL_Texture* enemyClosed;
};

struct GameState {
    uint32_t score;

    Player player;
    Enemy enemy;
    Enemy enemyClones[ENEMY_CLONE_AMOUNT];

    uint8_t controls;
};

typedef struct GameAssets GameAssets;
typedef struct GameState GameState;

#endif