#include "utils.h"

void StartGlide(Entity* entity, int32_t targetX, int32_t targetY, uint32_t duration) {
    entity->glideState.active = true;

    entity->glideState.startX = entity->rect.x;
    entity->glideState.startY = entity->rect.y;

    entity->glideState.targetX = targetX;
    entity->glideState.targetY = targetY;

    entity->glideState.startTime = SDL_GetTicks();
    entity->glideState.duration = duration;
}

void UpdateGlide(Entity* entity) {
    uint32_t currentTime = SDL_GetTicks();
    uint32_t elapsedTime = currentTime - entity->glideState.startTime;

    if (elapsedTime >= entity->glideState.duration) {
        entity->rect.x = entity->glideState.targetX;
        entity->rect.y = entity->glideState.targetY;

        entity->glideState.active = false;
    } else {
        float t = (float)elapsedTime / (float)entity->glideState.duration;

        entity->rect.x = (int32_t)(entity->glideState.startX + (entity->glideState.targetX - entity->glideState.startX) * t);
        entity->rect.y = (int32_t)(entity->glideState.startY + (entity->glideState.targetY - entity->glideState.startY) * t);
    }
}

void RenderScore(SDL_Renderer* renderer, TTF_Font* font, int32_t score) {
    SDL_Rect rect = SCORE_POSITION;
    SDL_Color color = SCORE_COLOR;

    char scoreText[16];

    snprintf(scoreText, sizeof(scoreText), "score: %d", score);
    TTF_SizeText(font, scoreText, &rect.w, &rect.h);

    SDL_Surface* surface = TTF_RenderText_Solid(font, scoreText, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_RenderCopy(renderer, texture, NULL, &rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}