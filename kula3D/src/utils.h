#ifndef UTILS_H
#define UTILS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <stdint.h>
#include <stdio.h>

#include "constants.h"

void RenderScore(SDL_Renderer* renderer, TTF_Font* font, int32_t score);

#endif