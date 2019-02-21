#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "MText.h"

MText::MText() {
  font = NULL;
}

MText::~MText() {
  free();
}

void MText::free() {
  if(font != NULL) {
    TTF_CloseFont(font);
    font = NULL;
  }
}

bool MText::loadFont(std::string f, int fontSize) {
  font = TTF_OpenFont(f.c_str(), fontSize);
  if(font == NULL) {
    printf( "Failed to load lazy font! SDL_ttf Error: %s\n",
      TTF_GetError() );
    return false;
  } else {
    return true;
  }
}

void MText::setColor(Uint8 r, Uint8 g, Uint8 b) {
  color = {r, g, b};
}

TTF_Font* MText::getFont() {
  return font;
}

SDL_Color MText::getColor() {
  return color;
}

