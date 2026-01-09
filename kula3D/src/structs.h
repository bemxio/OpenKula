#ifndef STRUCTS_H
#define STRUCTS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <stdbool.h>
#include <stdint.h>

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
    int32_t score;

    Player player;
    Enemy enemy;
    Enemy enemyClones[2];

    uint8_t controls;
};

typedef struct GameAssets GameAssets;
typedef struct GameState GameState;

#endif