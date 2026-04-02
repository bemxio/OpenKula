#ifndef UTILS_H
#define UTILS_H

#if defined(NXDK)
    #include <SDL.h>
    #include <SDL_ttf.h>
#else
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_ttf.h>
#endif

#include <stdbool.h>
#include <stdio.h>

#include "constants.h"
#include "structs.h"

void StartGlide(Entity* entity, Sint32 targetX, Sint32 targetY, Uint32 duration);
void UpdateGlide(Entity* entity);

void RenderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Rect rect, SDL_Color color);
void RenderScore(SDL_Renderer* renderer, TTF_Font* font, Sint32 score);

#endif