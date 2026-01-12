#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <stdbool.h>
#include <stdint.h>

#include "constants.h"
#include "structs.h"
#include "utils.h"

void GameLogic(GameState* state) {}

void GameRender(SDL_Renderer* renderer, GameState* state, GameAssets* assets) {
    SDL_RenderCopy(renderer, assets->background, NULL, NULL);
    RenderScore(renderer, assets->font, state->score);
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER);
    IMG_Init(0);
    TTF_Init();
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, GAME_WIDTH, GAME_HEIGHT, SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_GameController* controller = NULL;
    SDL_Event event;

    bool loop = true;

    GameState state = {
        .score = 0,

        .paddle = {
            .rect = PADDLE_INITIAL_RECT,
            .active = true,
            .glideState = {
                .active = false,

                .startX = 0, .startY = 0,
                .targetX = 0, .targetY = 0,

                .startTime = 0,
                .duration = 0
            }
        },
        .ball = {
            .rect = BALL_INITIAL_RECT,
            .active = true,
            .glideState = {
                .active = false,

                .startX = 0, .startY = 0,
                .targetX = 0, .targetY = 0,

                .startTime = 0,
                .duration = 0
            }
        },

        .controls = 0
    };

    GameAssets assets = {
        .background = IMG_LoadTexture(renderer, BACKGROUND_PATH),
        .music = Mix_LoadMUS(MUSIC_PATH),
        .font = TTF_OpenFont(FONT_PATH, SCORE_SIZE),

        .ball = IMG_LoadTexture(renderer, BALL_PATH)
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

                    switch (event.key.keysym.scancode) {
                        case SDL_SCANCODE_LEFT:
                            state.controls |= 1 << 0; break;
                        case SDL_SCANCODE_RIGHT:
                            state.controls |= 1 << 1; break;
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
                    }

                    break;

                case SDL_CONTROLLERBUTTONUP:
                    switch (event.cbutton.button) {
                        case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
                            state.controls &= ~(1 << 0); break;
                        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
                            state.controls &= ~(1 << 1); break;
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
    SDL_DestroyTexture(assets.ball);

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