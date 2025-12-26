#ifndef STRUCTS_H
#define STRUCTS_H

struct Entity {
    SDL_Rect rect;
};

struct Player {
    struct Entity;
};

struct Enemy {
    struct Entity;

    bool animationCycle;
    uint8_t animationTimer;
};

//typedef struct Entity Entity;
typedef struct Player Player;
typedef struct Enemy Enemy;

struct GameAssets {
    SDL_Texture* background;
    Mix_Music* music;

    SDL_Texture* player;
    SDL_Texture* enemyOpen;
    SDL_Texture* enemyClosed;    
};

struct GameState {
    Player player;
    Enemy enemy;
};

typedef struct GameAssets GameAssets;
typedef struct GameState GameState;

#endif