#ifndef UTILS_H
#define UTILS_H

#if defined(NXDK) || defined(__3DS__)
    #include <SDL.h>
    #include <SDL_ttf.h>
#else
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_ttf.h>
#endif

#include <stdio.h>

#include "constants.h"

void RenderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Rect rect, SDL_Color color);
void RenderScore(SDL_Renderer* renderer, TTF_Font* font, Sint32 score);
void RenderGameOver(SDL_Renderer* renderer, TTF_Font* font);

#endif