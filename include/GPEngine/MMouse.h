#ifndef MMOUSE_HEADER
#define MMOUSE_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "MGame.h"
#include "MEngine.h"

/*********************************************************************
  MMouse:
  SDL_Event notes: e->type SDL_MOUSEMOTION, SDK_MOUSEBUTTONDOWN, 
  SDL_MOUSEBUTTONUP, SDL_MOUSEWHEEL
  int x, y;
  SDL_GetMouseState( &x, &y );
  e->button SDL_BUTTON_LEFT, SDL_BUTTON_MIDDLE, SDL_BUTTON_RIGHT
  e->wheel.y > 0 Scroll up
  e->wheel.y < 0 Scroll down
  e->wheel.x > 0 Scroll right
  e->wheel.x < 0 Scroll left
  e->yrel relative mouse motion
  e->xrel relative mouse motion
  *May need to do e->button.*, need to test
  Author: Eric
 *********************************************************************/

class MEngine;

class MMouse {
  public:
    MMouse();
    ~MMouse();
    void init(MEngine*);
    void leftClickDown(int, int);
    void rightClickDown(int, int);
    void middleClickDown(int, int);
    void leftClickUp(int, int);
    void rightClickUp(int, int);
    void middleClickUp(int, int);
    void scrollDown(int, int);
    void scrollUp(int, int);
    void move(int, int);
  private:
    int x;
    int y;
    bool ldown;
    bool lup;
    bool rdown;
    bool rup;
    bool mdown;
    bool mup;
    MEngine* engine;
    int lx, ly;
    int rx, ry;
    int mx, my;
    void setxy(int, int);
};

#endif
