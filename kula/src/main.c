#include <stdbool.h>
#include <stdint.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "constants.h"
#include "structs.h"

void GameLogic(GameState* state) {
    if (!state->enemy.animationTimer) {
        state->enemy.animationTimer = ENEMY_ANIMATION_DELAY;
        state->enemy.animationCycle = !state->enemy.animationCycle;
    } else {
        state->enemy.animationTimer--;
    }
}

void GameRender(SDL_Renderer* renderer, GameState* state, GameAssets* assets) {
    SDL_RenderCopy(renderer, assets->background, NULL, NULL);
    SDL_RenderCopy(renderer, assets->player, NULL, &state->player.rect);
    SDL_RenderCopy(renderer, state->enemy.animationCycle ? assets->enemyClosed : assets->enemyOpen, NULL, &state->enemy.rect);
}

int main() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, GAME_WIDTH, GAME_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Event event;

    bool loop = true;

    GameState state = {
        .player = { .rect = {53, 298, 37, 34} },
        .enemy = { .rect = {447, 297, 45, 53} },
    };

    GameAssets assets = {
        .background = IMG_LoadTexture(renderer, BACKGROUND_PATH),
        .music = Mix_LoadMUS(BGM_PATH),

        .player = IMG_LoadTexture(renderer, PLAYER_PATH),
        .enemyOpen = IMG_LoadTexture(renderer, ENEMY_OPEN_PATH),
        .enemyClosed = IMG_LoadTexture(renderer, ENEMY_CLOSED_PATH),
    };

    Mix_PlayMusic(assets.music, -1);

    while (loop) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    loop = false; break;
            }
        }

        SDL_RenderClear(renderer);

        GameLogic(&state);
        GameRender(renderer, &state, &assets);

        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / FPS);
    }

    SDL_DestroyTexture(assets.background);
    Mix_FreeMusic(assets.music);
    SDL_DestroyTexture(assets.player);
    SDL_DestroyTexture(assets.enemyOpen);
    SDL_DestroyTexture(assets.enemyClosed);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    Mix_CloseAudio();
    Mix_Quit();

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}