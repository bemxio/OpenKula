#include "utils.h"

void RenderScore(SDL_Renderer* renderer, TTF_Font* font, int32_t score) {
    SDL_Rect rect = SCORE_POSITION;
    SDL_Color color = SCORE_COLOR;

    char scoreText[16];

    snprintf(scoreText, sizeof(scoreText), SCORE_TEXT, score);
    TTF_SizeText(font, scoreText, &rect.w, &rect.h);

    SDL_Surface* surface = TTF_RenderText_Solid(font, scoreText, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_RenderCopy(renderer, texture, NULL, &rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}