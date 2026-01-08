#ifndef UTILS_H
#define UTILS_H

#include <SDL2/SDL.h>

#include <stdbool.h>
#include <stdint.h>

#include "structs.h"

void StartGlide(Entity* entity, int32_t targetX, int32_t targetY, uint32_t duration);
void UpdateGlide(Entity* entity);

#endif