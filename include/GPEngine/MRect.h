#ifndef MRECT_HEADER
#define MRECT_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

//! Custom rectangle class. Can convert into SDL_Rect.
/*!
 *  The primary use of MRect is to act as a mediary to the underlying
 *  rectangle class. An MRect will simply have its (x,y) coordinate
 *  (anchored at top left) and width/height. You can convert an
 *  MRect to a SDL_Rect with the getSDLRect() member function.
 */

class MRect {
  public:
    int x, y, w, h;

    MRect()
      : x(0), y(0), w(0), h(0)
    { /* Nothing else to do */ }

    MRect(int _x, int _y, int _w, int _h)
      : x(_x), y(_y), w(_w), h(_h)
    { /* Nothing else to do */ }

    SDL_Rect getSDLRect() {
      SDL_Rect rect;
      rect.x = x;
      rect.y = y;
      rect.w = w;
      rect.h = h;
      return rect;
    }
};

#endif
