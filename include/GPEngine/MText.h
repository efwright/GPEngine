#ifndef MTEXT_HEADER
#define MTEXT_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class MText {
  public:
    MText();
    ~MText();
    void free();
    bool loadFont(std::string, int);
    void setColor(Uint8, Uint8, Uint8);
    TTF_Font* getFont();
    SDL_Color getColor();
  private:
    TTF_Font* font;
    SDL_Color color;
};

#endif
