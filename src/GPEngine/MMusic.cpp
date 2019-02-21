#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include "MMusic.h"

MMusic::MMusic() {
  music = NULL;
}

MMusic::~MMusic() {
  free();
}

void MMusic::free() {
  if(music != NULL) {
    Mix_FreeMusic(music);
    music = NULL;
  }
}

bool MMusic::load(std::string path) {
  free();
  music = Mix_LoadMUS(path.c_str());
  if(music == NULL) {
    printf( "Failed to load beat music! SDL_mixer Error: %s\n",
      Mix_GetError() );
    return false;
  } else { return true; }
}

void MMusic::play() {
  Mix_PlayMusic(music, -1);
}

bool MMusic::isPlaying() {
  return Mix_PlayingMusic() != 0;
}

void MMusic::pause() {
  Mix_PauseMusic();
}

void MMusic::unpause() {
  Mix_ResumeMusic();
}

