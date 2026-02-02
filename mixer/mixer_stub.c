#include "mixer.h"

void Mix_OpenAudio(int frequency, Uint16 format, int channels, int chunkSize) { return; }

Mix_Music* Mix_LoadMUS(const char* file) { return (void*)NULL; }
void Mix_PlayMusic(Mix_Music* music, int loops) { return; }

void Mix_SetMusicPosition(double position) { return; }
void Mix_ResumeMusic() { return; }
void Mix_PauseMusic() { return; }

void Mix_FreeMusic(Mix_Music* music) { return; }
void Mix_CloseAudio() { return; }
void Mix_Quit() { return; }