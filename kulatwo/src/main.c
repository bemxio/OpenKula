#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#include "constants.h"
#include "structs.h"
#include "utils.h"

void GameLogic(GameState* state) {
    if (state->controls & 1 << 0) {
        if (state->paddle.rect.x + (state->paddle.rect.w / 2) > 0) {
            state->paddle.rect.x -= PADDLE_SPEED;
        } else {
            state->paddle.rect.x = 0 - (state->paddle.rect.w / 2);
        }
    }

    if (state->controls & 1 << 1) {
        if (state->paddle.rect.x + (state->paddle.rect.w / 2) < GAME_WIDTH) {
            state->paddle.rect.x += PADDLE_SPEED;
        } else {
            state->paddle.rect.x = GAME_WIDTH - (state->paddle.rect.w / 2);
        }
    }

    if (!state->ball.glideState.active) {
        state->ball.rect.x += BALL_SPEED * cosf(state->ball.direction * (M_PI / 180.0f));
        state->ball.rect.y += BALL_SPEED * -sinf(state->ball.direction * (M_PI / 180.0f));

        if (state->ball.rect.x <= 0) {
            state->ball.rect.x = 0;
            state->ball.direction = 180.0f - state->ball.direction;
        } else if (state->ball.rect.x + state->ball.rect.w >= GAME_WIDTH) {
            state->ball.rect.x = GAME_WIDTH - state->ball.rect.w;
            state->ball.direction = 180.0f - state->ball.direction;
        }

        if (state->ball.rect.y <= 0) {
            state->ball.rect.y = 0;
            state->ball.direction = 360.0f - state->ball.direction;
        } else if (state->ball.rect.y + state->ball.rect.h >= GAME_HEIGHT) {
            state->ball.rect.y = GAME_HEIGHT - state->ball.rect.h;
            state->ball.direction = 360.0f - state->ball.direction;
        }
    } else {
        UpdateGlide((Entity*)&state->ball);
    }

    if (state->ball.paddleTimer == 0) {
        if (SDL_HasIntersection(&state->ball.rect, &state->paddle.rect)) {
            state->ball.direction += rand() % ((190 - 170) + 1) + 170;

            state->ball.rect.x += BALL_SPEED * cosf(state->ball.direction * (M_PI / 180.0f));
            state->ball.rect.y += BALL_SPEED * -sinf(state->ball.direction * (M_PI / 180.0f));

            state->score++;
            state->ball.paddleTimer = SDL_GetTicks() + BALL_PADDLE_COOLDOWN;
        }
    } else if (state->ball.paddleTimer <= SDL_GetTicks()) {
        state->ball.paddleTimer = 0;
    }

    if (SDL_HasIntersection(&state->ball.rect, &(SDL_Rect)BARRIER_RECT)) {
        state->score = 0;

        state->ball.rect.x = 14;
        state->ball.rect.y = 4;

        StartGlide((Entity*)&state->ball, 27, 298, BALL_GLIDE_DURATION);
    }
}

void GameRender(SDL_Renderer* renderer, GameState* state, GameAssets* assets) {
    SDL_RenderCopy(renderer, assets->background, NULL, NULL);

    SDL_SetRenderDrawColor(renderer, PADDLE_COLOR);
    SDL_RenderFillRect(renderer, &state->paddle.rect);

    SDL_SetRenderDrawColor(renderer, BARRIER_COLOR);
    SDL_RenderFillRect(renderer, &(SDL_Rect)BARRIER_RECT);

    SDL_RenderCopyEx(
        renderer, assets->ball,
        NULL, &state->ball.rect,
        -state->ball.direction, NULL, SDL_FLIP_NONE
    );

    RenderScore(renderer, assets->font, state->score);
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER);
    IMG_Init(0);
    TTF_Init();
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    srand(time(NULL));

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
            },

            .direction = BALL_INITIAL_DIRECTION
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

                case SDL_MOUSEMOTION:
                    state.paddle.rect.x = event.motion.x - (state.paddle.rect.w / 2); break;

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

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
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