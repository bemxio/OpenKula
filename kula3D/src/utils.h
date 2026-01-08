#ifndef UTILS_H
#define UTILS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "constants.h"
#include "structs.h"

void StartGlide(Entity* entity, int32_t targetX, int32_t targetY, uint32_t duration);
void UpdateGlide(Entity* entity);

void RenderScore(SDL_Renderer* renderer, TTF_Font* font, int32_t score);

#endif