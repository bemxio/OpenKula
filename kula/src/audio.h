#ifndef AUDIO_H
#define AUDIO_H

#define MIX_DEFAULT_FORMAT 0
#define Mix_Music void*

void Mix_OpenAudio(int, unsigned short, int, int);

void* Mix_LoadMUS(const char*);
void Mix_PlayMusic(void*, int);

void Mix_FreeMusic(void*);
void Mix_CloseAudio(void);
void Mix_Quit(void);

#endif