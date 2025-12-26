#ifndef STRUCTS_H
#define STRUCTS_H

struct GameAssets {
    SDL_Texture* background;
    Mix_Music* music;

    SDL_Texture* player;
    SDL_Texture* enemyOpen;
    SDL_Texture* enemyClosed;    
};

struct GameState {
    // TODO
};

typedef struct GameAssets GameAssets;
typedef struct GameState GameState;

#endif