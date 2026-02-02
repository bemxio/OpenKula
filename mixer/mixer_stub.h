#ifndef MIXER_H
#define MIXER_H

#define MIX_DEFAULT_FORMAT 0
#define Mix_Music void*

void Mix_OpenAudio(int, unsigned short, int, int);

Mix_Music* Mix_LoadMUS(const char*);
void Mix_PlayMusic(Mix_Music*, int);

void Mix_SetMusicPosition(double);
void Mix_ResumeMusic();
void Mix_PauseMusic();

void Mix_FreeMusic(void*);
void Mix_CloseAudio();
void Mix_Quit();

#endif