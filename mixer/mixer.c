#include "mixer.h"

void Mix_OpenAudio(int frequency, Uint16 format, int channels, int chunkSize) {
    return; // stub function, audio is opened in Mix_PlayMusic
}

Mix_Music* Mix_LoadMUS(const char* file) {
    Mix_Music* music = (Mix_Music*)malloc(sizeof(Mix_Music));
    SDL_LoadWAV(file, &music->spec, &music->buffer, &music->length);

    return music;
}

void Mix_PlayMusic(Mix_Music* music, int loops) {
    SDL_OpenAudio(&music->spec, NULL);
    SDL_QueueAudio(1, music->buffer, music->length);
    Mix_ResumeMusic();
}

void Mix_SetMusicPosition(double position) { 
    return; // stub function, not implemented yet
}

void Mix_ResumeMusic() { 
    SDL_PauseAudio(0);
}

void Mix_PauseMusic() { 
    SDL_PauseAudio(1);
}

void Mix_FreeMusic(Mix_Music* music) { 
    SDL_FreeWAV(music->buffer);
    free(music);
}

void Mix_CloseAudio() { 
    SDL_CloseAudio();
}

void Mix_Quit() { 
    return; // yet another stub, no need to do anything past Mix_CloseAudio
}