#include "mixer_stub.h"

void Mix_OpenAudio(int, unsigned short, int, int) { return; }

Mix_Music* Mix_LoadMUS(const char*) { return (void*)0; }
void Mix_PlayMusic(Mix_Music*, int) { return; }

void Mix_SetMusicPosition(double) { return; }
void Mix_ResumeMusic() { return; }
void Mix_PauseMusic() { return; }

void Mix_FreeMusic(void*) { return; }
void Mix_CloseAudio() { return; }
void Mix_Quit() { return; }