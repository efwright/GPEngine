#ifndef MFONT_HEADER
#define MFONT_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

//! Font Wrapper
/*!
 *  Currently stores the TTF_Font and font size.
 */

class MFont {
  public:
    MFont();
    ~MFont();

//! Load and initialize the font
    bool load(std::string path, int useFontSize);

    TTF_Font* getTTFFont();
    int getFontSize();
  private:
    TTF_Font* font;
    int fontSize;
};

#endif

