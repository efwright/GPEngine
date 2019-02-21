#ifndef MMUSIC_HEADER
#define MMUSIC_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

class MMusic {
  public:
    MMusic();
    ~MMusic();
    void free();
    bool load(std::string);
    void play();
    bool isPlaying();
    void pause();
    void unpause();
  private:
    Mix_Music* music;
};

#endif
