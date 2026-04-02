#if defined(NXDK)
    #include <hal/video.h>

    #include <SDL.h>
    #include <SDL_image.h>
    #include <SDL_ttf.h>

    #include "../../mixer/mixer.h"
#else
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
    #include <SDL2/SDL_mixer.h>
    #include <SDL2/SDL_ttf.h>
#endif

#include <emscripten.h>

#include <stdbool.h>

#include "constants.h"
#include "structs.h"
#include "utils.h"

struct App {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_GameController* controller;

    GameState state;
    GameAssets assets;

    bool loop;
    bool audioStarted;

    int screenWidth;
    int screenHeight;
};

typedef struct App App;

void GameReset(GameState* state, bool resumeMusic) {
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

    for (size_t i = 0; i < ENEMY_CLONE_AMOUNT; i++) {
        state->enemyClones[i].rect = (SDL_Rect)ENEMY_INITIAL_RECT;
        state->enemyClones[i].active = false;
        state->enemyClones[i].hidden = true;
    }

    state->score = 0;

    if (resumeMusic) {
        Mix_SetMusicPosition(0);
        Mix_ResumeMusic();
    }
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

    for (size_t i = 0; i < ENEMY_CLONE_AMOUNT; i++) {
        if (state->enemyClones[i].active) {
            state->enemyClones[i].rect.x -= ENEMY_SPEED;

            if (state->enemyClones[i].rect.x <= 0) {
                state->enemyClones[i].active = false;
                state->enemyClones[i].hidden = true;
            }

            if (SDL_HasIntersection(&state->player.rect, &state->enemyClones[i].rect)) {
                state->player.active = false;
                state->enemy.active = false;

                for (size_t j = 0; j < ENEMY_CLONE_AMOUNT; j++) {
                    state->enemyClones[j].active = false;
                }

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

                for (size_t i = 0; i < ENEMY_CLONE_AMOUNT; i++) {
                    if (state->enemyClones[i].active) continue;

                    state->enemyClones[i].rect = (SDL_Rect)ENEMY_INITIAL_RECT;
                    state->enemyClones[i].active = true;
                    state->enemyClones[i].hidden = false;

                    break;
                }
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

static GameState GameStateCreate(void) {
    return (GameState) {
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
}

static GameAssets GameAssetsLoad(SDL_Renderer* renderer) {
    return (GameAssets) {
        .background = IMG_LoadTexture(renderer, BACKGROUND_PATH),
        .logo = IMG_LoadTexture(renderer, LOGO_PATH),
        .music = Mix_LoadMUS(BGM_PATH),
        .font = TTF_OpenFont(FONT_PATH, FONT_INITIAL_SIZE),

        .player = IMG_LoadTexture(renderer, PLAYER_PATH),
        .enemyOpen = IMG_LoadTexture(renderer, ENEMY_OPEN_PATH),
        .enemyClosed = IMG_LoadTexture(renderer, ENEMY_CLOSED_PATH)
    };
}

static void AppUpdateRenderScale(App* app, int width, int height) {
    app->screenWidth = width;
    app->screenHeight = height;

    SDL_RenderSetScale(
        app->renderer,
        (float)width / GAME_WIDTH,
        (float)height / GAME_HEIGHT
    );
}

static void AppStartMusic(App* app) {
    if (app->audioStarted || app->assets.music == NULL) {
        return;
    }

    Mix_PlayMusic(app->assets.music, -1);
    app->audioStarted = true;
}

static void AppHandleEvent(App* app, const SDL_Event* event) {
    switch (event->type) {
        case SDL_QUIT:
            app->loop = false; break;

        case SDL_WINDOWEVENT:
            if (event->window.event == SDL_WINDOWEVENT_RESIZED) {
                AppUpdateRenderScale(app, event->window.data1, event->window.data2);
            }

            break;

        case SDL_KEYDOWN:
            if (event->key.repeat) break;

            AppStartMusic(app);

            switch (event->key.keysym.scancode) {
                case SDL_SCANCODE_LEFT:
                    app->state.controls |= 1 << 0; break;
                case SDL_SCANCODE_RIGHT:
                    app->state.controls |= 1 << 1; break;
                case SDL_SCANCODE_SPACE:
                    app->state.controls |= 1 << 2; break;
                case SDL_SCANCODE_RETURN:
                    if (!app->state.player.active) {
                        GameReset(&app->state, app->audioStarted);
                    }

                    break;
                default:
                    break;
            }

            break;

        case SDL_KEYUP:
            switch (event->key.keysym.scancode) {
                case SDL_SCANCODE_LEFT:
                    app->state.controls &= ~(1 << 0); break;
                case SDL_SCANCODE_RIGHT:
                    app->state.controls &= ~(1 << 1); break;
                case SDL_SCANCODE_SPACE:
                    app->state.controls &= ~(1 << 2); break;
                default:
                    break;
            }

            break;

        case SDL_CONTROLLERDEVICEADDED:
            if (app->controller == NULL) {
                app->controller = SDL_GameControllerOpen(event->cdevice.which);
            }

            break;

        case SDL_CONTROLLERDEVICEREMOVED:
            if (SDL_GameControllerFromInstanceID(event->cdevice.which) == app->controller) {
                SDL_GameControllerClose(app->controller);
                app->controller = NULL;
            }

            break;

        case SDL_CONTROLLERBUTTONDOWN:
            AppStartMusic(app);

            switch (event->cbutton.button) {
                case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
                    app->state.controls |= 1 << 0; break;
                case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
                    app->state.controls |= 1 << 1; break;
                case SDL_CONTROLLER_BUTTON_A:
                    app->state.controls |= 1 << 2; break;
                case SDL_CONTROLLER_BUTTON_START:
                    if (!app->state.player.active) {
                        GameReset(&app->state, app->audioStarted);
                    }

                    break;
                case SDL_CONTROLLER_BUTTON_BACK:
                    app->loop = false; break;
            }

            break;

        case SDL_CONTROLLERBUTTONUP:
            switch (event->cbutton.button) {
                case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
                    app->state.controls &= ~(1 << 0); break;
                case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
                    app->state.controls &= ~(1 << 1); break;
                case SDL_CONTROLLER_BUTTON_A:
                    app->state.controls &= ~(1 << 2); break;
            }

            break;
    }
}

static void AppShutdown(App* app) {
    SDL_DestroyTexture(app->assets.background);
    SDL_DestroyTexture(app->assets.logo);
    Mix_FreeMusic(app->assets.music);
    TTF_CloseFont(app->assets.font);
    SDL_DestroyTexture(app->assets.player);
    SDL_DestroyTexture(app->assets.enemyOpen);
    SDL_DestroyTexture(app->assets.enemyClosed);

    if (app->controller != NULL) SDL_GameControllerClose(app->controller);
    SDL_DestroyRenderer(app->renderer);
    SDL_DestroyWindow(app->window);

    Mix_CloseAudio();
    Mix_Quit();

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

static void AppTick(void* userdata) {
    App* app = userdata;
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        AppHandleEvent(app, &event);
    }

    if (!app->loop) {
        emscripten_cancel_main_loop();
        AppShutdown(app);

        return;
    }

    SDL_RenderClear(app->renderer);

    GameLogic(&app->state);
    GameRender(app->renderer, &app->state, &app->assets);

    SDL_RenderPresent(app->renderer);
}

int main(int argc, char* argv[]) {
    #if defined(NXDK)
        XVideoSetMode(640, 480, 32, REFRESH_DEFAULT);
    #endif

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    SDL_Window* window = SDL_CreateWindow(
        WINDOW_TITLE,
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        #if defined(__wii__) || defined(NXDK)
            640, 480,
        #elif defined(__vita__)
            960, 544,
        #elif defined(PSP)
            480, 272,
        #elif defined(__PPU__)
            1280, 720,
        #else
            GAME_WIDTH, GAME_HEIGHT,
        #endif
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    App app = {
        .window = window,
        .renderer = renderer,
        .controller = NULL,
        .state = GameStateCreate(),
        .assets = GameAssetsLoad(renderer),
        .loop = true,
        .audioStarted = false,
        .screenWidth = 0,
        .screenHeight = 0
    };

    SDL_GetWindowSize(window, &app.screenWidth, &app.screenHeight);
    AppUpdateRenderScale(&app, app.screenWidth, app.screenHeight);

    #if defined(__wii__)
        SDL_ShowCursor(SDL_DISABLE);
    #endif

    emscripten_set_main_loop_arg(AppTick, &app, FPS, true);

    return 0;
}
