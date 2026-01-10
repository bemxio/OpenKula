#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <stdbool.h>
#include <stdint.h>

#include "constants.h"
#include "structs.h"
#include "utils.h"

void GameReset(GameState* state) {
    state->player.rect = (SDL_Rect)PLAYER_INITIAL_RECT;
    state->player.active = true;
    state->player.hidden = false;
    state->player.jumpCycle = false;
    state->player.jumpTimer = 0;

    state->enemy.rect = (SDL_Rect)ENEMY_INITIAL_RECT;
    state->enemy.active = true;
    state->enemy.hidden = false;
    state->enemy.ghostTimer = 0;
    state->enemy.cloneTimer = 0;

    for (size_t i = 0; i < 2; i++) {
        state->enemyClones[i].rect = (SDL_Rect)ENEMY_INITIAL_RECT;
        state->enemyClones[i].active = false;
        state->enemyClones[i].hidden = true;
    }

    state->score = 0;

    Mix_SetMusicPosition(0);
    Mix_ResumeMusic();
}

void GameLogic(GameState* state) {
    if (state->player.active) {
        if (state->controls & 1 << 0) {
            if (state->player.rect.x + (state->player.rect.w / 2) > 0) {
                state->player.rect.x -= PLAYER_SPEED;
            } else {
                state->player.rect.x = 0 - (state->player.rect.w / 2);
            }
        }

        if (state->controls & 1 << 1) {
            if (state->player.rect.x + (state->player.rect.w / 2) < GAME_WIDTH) {
                state->player.rect.x += PLAYER_SPEED;
            } else {
                state->player.rect.x = GAME_WIDTH - (state->player.rect.w / 2);
            }
        }

        if (state->controls & 1 << 2) {
            if (state->player.jumpTimer == 0 && !state->player.jumpCycle) {
                state->player.jumpCycle = true;
                state->player.jumpTimer = 10;
            }
        }

        if (state->player.jumpCycle) {
            state->player.rect.y -= PLAYER_SPEED;
            state->player.jumpTimer--;

            if (state->player.jumpTimer == 0) {
                state->player.jumpCycle = false;
                state->player.jumpTimer = 10;
            }
        } else if (state->player.jumpTimer > 0) {
            state->player.rect.y += PLAYER_SPEED;
            state->player.jumpTimer--;
        }
    }

    for (size_t i = 0; i < 2; i++) {
        if (state->enemyClones[i].active) {
            state->enemyClones[i].rect.x -= ENEMY_SPEED;

            if (state->enemyClones[i].rect.x <= 0) {
                state->enemyClones[i].active = false;
                state->enemyClones[i].hidden = true;
            }

            if (SDL_HasIntersection(&state->player.rect, &state->enemyClones[i].rect)) {
                state->player.active = false;
                state->enemy.active = false;

                state->enemyClones[0].active = false;
                state->enemyClones[1].active = false;

                Mix_PauseMusic();
            }
        }
    }

    if (state->enemy.active) {
        if (state->enemy.cloneTimer == 0) {
            if (state->enemy.ghostTimer == 0) {
                state->enemy.rect.x -= ENEMY_SPEED;

                if (state->enemy.rect.x <= 0) {
                    state->score++;

                    state->enemy.rect.x = 0;
                    state->enemy.ghostTimer = SDL_GetTicks() + ENEMY_GHOST_DURATION;
                }
            } else if (state->enemy.ghostTimer <= SDL_GetTicks()) {
                state->enemy.hidden = true;

                state->enemy.ghostTimer = 0;
                state->enemy.cloneTimer = SDL_GetTicks() + ENEMY_CLONE_INTERVAL;

                size_t i = !state->enemyClones[0].active ? 0 : 1;

                state->enemyClones[i].rect = (SDL_Rect)ENEMY_INITIAL_RECT;
                state->enemyClones[i].active = true;
                state->enemyClones[i].hidden = false;
            }
        } else if (state->enemy.cloneTimer <= SDL_GetTicks()) {
            state->enemy.cloneTimer = 0;
        }

        if (!state->enemy.hidden && SDL_HasIntersection(&state->player.rect, &state->enemy.rect)) {
            state->player.active = false;
            state->enemy.active = false;

            Mix_PauseMusic();
        }
    }
}

void GameRender(SDL_Renderer* renderer, GameState* state, GameAssets* assets) {
    SDL_RenderCopy(renderer, assets->background, NULL, NULL);

    for (size_t i = 0; i < 2; i++) {
        if (!state->enemyClones[i].hidden) {
            SDL_RenderCopy(renderer, state->enemyClones[i].active ? assets->enemyOpen : assets->enemyClosed, NULL, &state->enemyClones[i].rect);
        }
    }

    if (!state->enemy.hidden) SDL_RenderCopy(renderer, state->enemy.active ? assets->enemyOpen : assets->enemyClosed, NULL, &state->enemy.rect);
    if (!state->player.hidden) SDL_RenderCopy(renderer, assets->player, NULL, &state->player.rect);

    SDL_RenderCopy(renderer, assets->logo, NULL, &(SDL_Rect)LOGO_RECT);
    RenderScore(renderer, assets->font, state->score);

    if (!state->player.active) RenderGameOver(renderer, assets->font);
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, GAME_WIDTH, GAME_HEIGHT, SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_GameController* controller = NULL;
    SDL_Event event;

    bool loop = true;

    GameState state = {
        .score = 0,

        .player = {
            .rect = PLAYER_INITIAL_RECT,
            .active = true,
            .hidden = false,

            .jumpCycle = false,
            .jumpTimer = 0
        },

        .enemy = { .rect = ENEMY_INITIAL_RECT, .active = true, .hidden = false, .ghostTimer = 0, .cloneTimer = 0 },
        .enemyClones = {
            { .rect = ENEMY_INITIAL_RECT, .active = false, .hidden = true },
            { .rect = ENEMY_INITIAL_RECT, .active = false, .hidden = true }
        },

        .controls = 0
    };

    GameAssets assets = {
        .background = IMG_LoadTexture(renderer, BACKGROUND_PATH),
        .logo = IMG_LoadTexture(renderer, LOGO_PATH),
        .music = Mix_LoadMUS(BGM_PATH),
        .font = TTF_OpenFont(FONT_PATH, 0),

        .player = IMG_LoadTexture(renderer, PLAYER_PATH),
        .enemyOpen = IMG_LoadTexture(renderer, ENEMY_OPEN_PATH),
        .enemyClosed = IMG_LoadTexture(renderer, ENEMY_CLOSED_PATH)
    };

    SDL_RenderSetLogicalSize(renderer, GAME_WIDTH, GAME_HEIGHT);
    Mix_PlayMusic(assets.music, -1);

    while (loop) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    loop = false; break;

                case SDL_KEYDOWN:
                    if (event.key.repeat) break;

                    switch (event.key.keysym.sym) {
                        case SDLK_LEFT:
                            state.controls |= 1 << 0; break;
                        case SDLK_RIGHT:
                            state.controls |= 1 << 1; break;
                        case SDLK_SPACE:
                            state.controls |= 1 << 2; break;
                        case SDLK_RETURN:
                            if (!state.player.active) {
                                GameReset(&state);
                            }

                            break;
                        case SDLK_ESCAPE:
                            loop = false; break;
                    }

                    break;

                case SDL_KEYUP:
                    switch (event.key.keysym.sym) {
                        case SDLK_LEFT:
                            state.controls &= ~(1 << 0); break;
                        case SDLK_RIGHT:
                            state.controls &= ~(1 << 1); break;
                        case SDLK_SPACE:
                            state.controls &= ~(1 << 2); break;
                    }

                    break;

                case SDL_CONTROLLERDEVICEADDED:
                    if (controller == NULL) {
                        controller = SDL_GameControllerOpen(event.cdevice.which);
                    }

                    break;

                case SDL_CONTROLLERDEVICEREMOVED:
                    if (SDL_GameControllerFromInstanceID(event.cdevice.which) == controller) {
                        SDL_GameControllerClose(controller); controller = NULL;
                    }

                    break;

                case SDL_CONTROLLERBUTTONDOWN:
                    switch (event.cbutton.button) {
                        case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
                            state.controls |= 1 << 0; break;
                        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
                            state.controls |= 1 << 1; break;
                        case SDL_CONTROLLER_BUTTON_A:
                            state.controls |= 1 << 2; break;
                        case SDL_CONTROLLER_BUTTON_START:
                            if (!state.player.active) {
                                GameReset(&state);
                            }

                            break;
                        case SDL_CONTROLLER_BUTTON_GUIDE:
                            loop = false; break;
                    }

                    break;

                case SDL_CONTROLLERBUTTONUP:
                    switch (event.cbutton.button) {
                        case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
                            state.controls &= ~(1 << 0); break;
                        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
                            state.controls &= ~(1 << 1); break;
                        case SDL_CONTROLLER_BUTTON_A:
                            state.controls &= ~(1 << 2); break;
                    }

                    break;
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
    TTF_CloseFont(assets.font);
    SDL_DestroyTexture(assets.player);
    SDL_DestroyTexture(assets.enemyOpen);
    SDL_DestroyTexture(assets.enemyClosed);

    if (controller != NULL) SDL_GameControllerClose(controller);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    Mix_CloseAudio();
    Mix_Quit();

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}