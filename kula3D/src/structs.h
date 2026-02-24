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

#include "constants.h"

struct Entity {
    SDL_Rect rect;
    bool active;
    bool hidden;
};

struct Player {
    struct Entity;

    bool jumpCycle;
    Uint8 jumpTimer;
};

struct Enemy {
    struct Entity;

    Uint32 ghostTimer;
    Uint32 cloneTimer;
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
    Uint32 score;

    Player player;
    Enemy enemy;
    Enemy enemyClones[ENEMY_CLONE_AMOUNT];

    Uint8 controls;
};

typedef struct GameAssets GameAssets;
typedef struct GameState GameState;

#endif