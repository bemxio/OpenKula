#ifndef MIXER_H
#define MIXER_H

#include <SDL_audio.h>
#include <stdlib.h>

#define MIX_DEFAULT_FORMAT AUDIO_S16SYS

typedef struct Mix_Music {
    Uint32 length;
    Uint8* buffer;
    SDL_AudioSpec spec;
} Mix_Music;

void Mix_OpenAudio(int frequency, Uint16 format, int channels, int chunkSize);

Mix_Music* Mix_LoadMUS(const char* file);
void Mix_PlayMusic(Mix_Music* music, int loops);

void Mix_SetMusicPosition(double position);
void Mix_ResumeMusic();
void Mix_PauseMusic();

void Mix_FreeMusic(Mix_Music* music);
void Mix_CloseAudio();
void Mix_Quit();

#endif