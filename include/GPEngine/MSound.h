#ifndef MSOUND_HEADER
#define MSOUND_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

class MSound {
  public:
    MSound();
    ~MSound();
    void free();
    bool load(std::string);
    void play();
  private:
    Mix_Chunk* chunk;
};

#endif
