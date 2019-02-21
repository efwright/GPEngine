#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include "MSound.h"

MSound::MSound() {
  chunk = NULL;
}

MSound::~MSound() {
  free();
}

void MSound::free() {
  if(chunk != NULL) {
    Mix_FreeChunk(chunk);
    chunk = NULL;
  }
}

bool MSound::load(std::string path) {
  free();
  chunk = Mix_LoadWAV(path.c_str());
  if(chunk == NULL) {
    printf( "Failed to load scratch sound! SDL_mixer Error: %s\n",
      Mix_GetError() );
    return false;
  } else { return true; }
}

void MSound::play() {
  Mix_PlayChannel( -1, chunk, 0 );
}

