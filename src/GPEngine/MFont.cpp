#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "MFont.h"

MFont::MFont() {
  font = NULL;
  fontSize = 0;
}

MFont::~MFont() {
  if(font != NULL) {
    TTF_CloseFont(font);
    font = NULL;
  }
  fontSize = 0;
}

bool MFont::load(std::string path, int useFontSize) {
  fontSize = useFontSize;
  font = TTF_OpenFont(path.c_str(), fontSize);
  if(font == NULL) {
    printf("Failed to load font %s: SDL_ttf Error: %s\n",
      path.c_str(), TTF_GetError());
  }
  return font != NULL;
}

TTF_Font* MFont::getTTFFont() {
  return font;
}

int MFont::getFontSize() {
  return fontSize;
}

