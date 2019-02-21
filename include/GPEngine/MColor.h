#ifndef MCOLOR_HEADER
#define MCOLOR_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string>

//! Store r,g,b value of color. Wrapper for SDL_Color

class MColor {
  public:
    Uint8 r, g, b;	
    MColor()
      : r(0), g(0), b(0) { };
    MColor(Uint8 red, Uint8 green, Uint8 blue)
      : r(red), g(green), b(blue) { };
    ~MColor(){}
};

#endif
