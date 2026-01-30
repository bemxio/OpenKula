#include "audio.h"

void Mix_OpenAudio(int, unsigned short, int, int) { return; }

void* Mix_LoadMUS(const char*) { return (void*)0; }
void Mix_PlayMusic(void*, int) { return; }

void Mix_SetMusicPosition(double) { return; }
void Mix_ResumeMusic(void) { return; }
void Mix_PauseMusic(void) { return; }

void Mix_FreeMusic(void*) { return; }
void Mix_CloseAudio(void) { return; }
void Mix_Quit(void) { return; }