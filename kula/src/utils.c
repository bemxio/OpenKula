#include "utils.h"

void StartGlide(Entity* entity, Sint32 targetX, Sint32 targetY, Uint32 duration) {
    entity->glideState.active = true;

    entity->glideState.startX = entity->rect.x;
    entity->glideState.startY = entity->rect.y;

    entity->glideState.targetX = targetX;
    entity->glideState.targetY = targetY;

    entity->glideState.startTime = SDL_GetTicks();
    entity->glideState.duration = duration;
}

void UpdateGlide(Entity* entity) {
    Uint32 currentTime = SDL_GetTicks();
    Uint32 elapsedTime = currentTime - entity->glideState.startTime;

    if (elapsedTime >= entity->glideState.duration) {
        entity->rect.x = entity->glideState.targetX;
        entity->rect.y = entity->glideState.targetY;

        entity->glideState.active = false;
    } else {
        float t = (float)elapsedTime / (float)entity->glideState.duration;

        entity->rect.x = (Sint32)(entity->glideState.startX + (entity->glideState.targetX - entity->glideState.startX) * t);
        entity->rect.y = (Sint32)(entity->glideState.startY + (entity->glideState.targetY - entity->glideState.startY) * t);
    }
}

void RenderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Rect rect, SDL_Color color) {
    SDL_Surface* surface = TTF_RenderText_Blended(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_RenderCopy(renderer, texture, NULL, &rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void RenderScore(SDL_Renderer* renderer, TTF_Font* font, Sint32 score) {
    SDL_Rect rect = SCORE_RECT;
    char buffer[18];

    snprintf(buffer, sizeof(buffer), SCORE_TEXT, score);

    //TTF_SetFontSize(font, SCORE_SIZE);
    TTF_SizeText(font, buffer, &rect.w, &rect.h);

    RenderText(renderer, font, buffer, rect, (SDL_Color)SCORE_COLOR);
}