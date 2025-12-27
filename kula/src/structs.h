#ifndef STRUCTS_H
#define STRUCTS_H

struct Entity {
    SDL_Rect rect;
    bool active;
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