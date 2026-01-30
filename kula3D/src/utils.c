#include "utils.h"

void RenderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Rect rect, SDL_Color color) {
    SDL_Surface* surface = TTF_RenderText_Blended(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_RenderCopy(renderer, texture, NULL, &rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void RenderScore(SDL_Renderer* renderer, TTF_Font* font, int32_t score) {
    SDL_Rect rect = SCORE_RECT;
    char buffer[18];

    snprintf(buffer, sizeof(buffer), SCORE_TEXT, score);
    TTF_SizeText(font, buffer, &rect.w, &rect.h);

    rect.w *= SCORE_SIZE / (float)FONT_INITIAL_SIZE;
    rect.h *= SCORE_SIZE / (float)FONT_INITIAL_SIZE;

    RenderText(renderer, font, buffer, rect, (SDL_Color)SCORE_COLOR);
}

void RenderGameOver(SDL_Renderer* renderer, TTF_Font* font) {
    SDL_Rect captionRect;
    SDL_Rect subcaptionRect;

    TTF_SizeText(font, GAME_OVER_CAPTION_TEXT, &captionRect.w, &captionRect.h);
    TTF_SizeText(font, GAME_OVER_SUBCAPTION_TEXT, &subcaptionRect.w, &subcaptionRect.h);

    captionRect.w *= GAME_OVER_CAPTION_SIZE / (float)FONT_INITIAL_SIZE;
    captionRect.h *= GAME_OVER_CAPTION_SIZE / (float)FONT_INITIAL_SIZE;
    subcaptionRect.w *= GAME_OVER_SUBCAPTION_SIZE / (float)FONT_INITIAL_SIZE;
    subcaptionRect.h *= GAME_OVER_SUBCAPTION_SIZE / (float)FONT_INITIAL_SIZE;

    captionRect.x = (GAME_WIDTH - captionRect.w) / 2;
    captionRect.y = (GAME_HEIGHT - captionRect.h) / 2 - GAME_OVER_SPACING;
    subcaptionRect.x = (GAME_WIDTH - subcaptionRect.w) / 2;
    subcaptionRect.y = (GAME_HEIGHT - subcaptionRect.h) / 2 + GAME_OVER_SPACING;

    RenderText(renderer, font, GAME_OVER_CAPTION_TEXT, captionRect, (SDL_Color)GAME_OVER_COLOR);
    RenderText(renderer, font, GAME_OVER_SUBCAPTION_TEXT, subcaptionRect, (SDL_Color)GAME_OVER_COLOR);
}