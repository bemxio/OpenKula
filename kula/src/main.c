#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <stdbool.h>
#include <stdint.h>

#include "constants.h"
#include "structs.h"
#include "utils.h"

void GameLogic(GameState* state) {
    if (!state->player.glideState.active) {
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
    } else {
        UpdateGlide((Entity*)&state->player);
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

    if (state->enemy.active) {
        SDL_Rect scoreHitbox = {
            .x = state->enemy.rect.x - 6,
            .y = state->enemy.rect.y - 97,
            .w = 50, .h = 54
        };

        if (state->scoreTimer == 0 && SDL_HasIntersection(&state->player.rect, &scoreHitbox)) {
            state->scoreTimer = SDL_GetTicks() + 200;
        }

        if (SDL_HasIntersection(&state->player.rect, &state->enemy.rect)) {
            state->player.rect.x = 24;
            state->player.rect.y = -18;

            state->player.jumpTimer = 0;
            state->player.jumpCycle = false;

            state->score = 0;
            state->scoreTimer = 0;

            StartGlide((Entity*)&state->player, 30, 309, PLAYER_GLIDE_DURATION);
        }
    }

    if (state->scoreTimer != 0 && state->scoreTimer <= SDL_GetTicks()) {
        state->scoreTimer = 0;
        state->score++;
    }

    if (!state->enemy.glideState.active) {
        if (state->enemy.ghostTimer <= SDL_GetTicks()) {
            state->enemy.active = true;
            state->enemy.rect.x = 447;

            StartGlide((Entity*)&state->enemy, -15, 294, ENEMY_GLIDE_DURATION);
        } else {
            state->enemy.active = false;
            state->enemy.ghostTimer = SDL_GetTicks() + ENEMY_GHOST_DURATION;
        }
    } else {
        UpdateGlide((Entity*)&state->enemy);
    }

    if (state->enemy.mouthTimer == 0) {
        state->enemy.mouthTimer = ENEMY_ANIMATION_DELAY;
        state->enemy.mouthCycle = !state->enemy.mouthCycle;
    } else {
        state->enemy.mouthTimer--;
    }
}

void GameRender(SDL_Renderer* renderer, GameState* state, GameAssets* assets) {
    SDL_RenderCopy(renderer, assets->background, NULL, NULL);

    if (state->enemy.active) SDL_RenderCopy(renderer, state->enemy.mouthCycle ? assets->enemyClosed : assets->enemyOpen, NULL, &state->enemy.rect);
    if (state->player.active) SDL_RenderCopy(renderer, assets->player, NULL, &state->player.rect);

    RenderScore(renderer, assets->font, state->score);
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    #ifdef __wii__
        SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        SDL_Texture* target = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_TARGET, GAME_WIDTH, GAME_HEIGHT);
    #elif __vita__
        SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 960, 544, SDL_WINDOW_SHOWN);
        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);    
    #else
        SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, GAME_WIDTH, GAME_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    #endif

    SDL_GameController* controller = NULL;
    SDL_Event event;

    bool loop = true;

    GameState state = {
        .score = 0,
        .scoreTimer = 0,

        .player = {
            .rect = PLAYER_INITIAL_RECT,
            .active = true,
            .glideState = {
                .active = false,

                .startX = 0, .startY = 0,
                .targetX = 0, .targetY = 0,

                .startTime = 0,
                .duration = 0
            },

            .jumpCycle = false,
            .jumpTimer = 0
        },
        .enemy = {
            .rect = ENEMY_INITIAL_RECT,
            .active = true,
            .glideState = {
                .active = false,

                .startX = 0, .startY = 0,
                .targetX = 0, .targetY = 0,

                .startTime = 0,
                .duration = 0
            },

            .mouthCycle = false,
            .mouthTimer = 0,
            .ghostTimer = 0
        },

        .controls = 0
    };
    GameAssets assets = {
        .background = IMG_LoadTexture(renderer, BACKGROUND_PATH),
        .music = Mix_LoadMUS(BGM_PATH),
        .font = TTF_OpenFont(FONT_PATH, SCORE_SIZE),

        .player = IMG_LoadTexture(renderer, PLAYER_PATH),
        .enemyOpen = IMG_LoadTexture(renderer, ENEMY_OPEN_PATH),
        .enemyClosed = IMG_LoadTexture(renderer, ENEMY_CLOSED_PATH)
    };

    #ifdef __wii__
        SDL_ShowCursor(SDL_DISABLE);
    #endif

    Mix_PlayMusic(assets.music, -1);

    while (loop) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    loop = false; break;

                case SDL_WINDOWEVENT:
                    if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                        SDL_RenderSetScale(renderer,
                            (float)event.window.data1 / GAME_WIDTH,
                            (float)event.window.data2 / GAME_HEIGHT
                        );
                    }

                    break;

                case SDL_KEYDOWN:
                    if (event.key.repeat) break;

                    switch (event.key.keysym.scancode) {
                        case SDL_SCANCODE_LEFT:
                            state.controls |= 1 << 0; break;
                        case SDL_SCANCODE_RIGHT:
                            state.controls |= 1 << 1; break;
                        case SDL_SCANCODE_SPACE:
                            state.controls |= 1 << 2; break;
                        default:
                            break;
                    }

                    break;

                case SDL_KEYUP:
                    switch (event.key.keysym.scancode) {
                        case SDL_SCANCODE_LEFT:
                            state.controls &= ~(1 << 0); break;
                        case SDL_SCANCODE_RIGHT:
                            state.controls &= ~(1 << 1); break;
                        case SDL_SCANCODE_SPACE:
                            state.controls &= ~(1 << 2); break;
                        default:
                            break;
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
                        case SDL_CONTROLLER_BUTTON_BACK:
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

        #ifdef __wii__
            SDL_SetRenderTarget(renderer, target);
        #endif

        GameLogic(&state);
        GameRender(renderer, &state, &assets);

        #ifdef __wii__
            SDL_SetRenderTarget(renderer, NULL);
            SDL_RenderCopy(renderer, target, NULL, NULL);
        #endif

        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / FPS);
    }

    SDL_DestroyTexture(assets.background);
    Mix_FreeMusic(assets.music);
    TTF_CloseFont(assets.font);
    SDL_DestroyTexture(assets.player);
    SDL_DestroyTexture(assets.enemyOpen);
    SDL_DestroyTexture(assets.enemyClosed);

    #ifdef __wii__
        SDL_DestroyTexture(target);
    #endif

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