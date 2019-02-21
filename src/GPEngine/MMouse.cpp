#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "MMouse.h"
#include "MGame.h"
#include "MEngine.h"
#include "MMouseInterface.h"

MMouse::MMouse() {
  x = 0;
  y = 0;
  ldown = false;
  lup = false;
  rdown = false;
  rup = false;
  mdown = false;
  mup = false;
  engine = NULL;
}

MMouse::~MMouse() {
  x = 0;
  y = 0;
  ldown = false;
  lup = false;
  rdown = false;
  rup = false;
  mdown = false;
  mup = false;
  engine = NULL;
}

void MMouse::init(MEngine* e) {
  engine = e;
}

void MMouse::setxy(int mousex, int mousey) {
  x = mousex;
  y = mousey;
}

void MMouse::leftClickDown(int mousex, int mousey) {
  setxy(mousex, mousey);
  lx = mousex;
  ly = mousey;
  ldown = true;
  lup = false;
  engine->getMouseI()->leftClickDown(x, y);
}

void MMouse::rightClickDown(int mousex, int mousey) {
  setxy(mousex, mousey);
  rx = mousex;
  ry = mousey;
  rdown = true;
  rup = false;
  engine->getMouseI()->rightClickDown(x, y);
}

void MMouse::middleClickDown(int mousex, int mousey) {
  setxy(mousex, mousey);
  mx = mousex;
  my = mousey;
  mdown = true;
  mup = false;
  engine->getMouseI()->middleClickDown(x, y);
}

void MMouse::leftClickUp(int mousex, int mousey) {
  setxy(mousex, mousey);
  ldown = false;
  lup = true;
  engine->getMouseI()->leftClickUp(x, y);
}

void MMouse::rightClickUp(int mousex, int mousey) {
  setxy(mousex, mousey);
  rdown = false;
  rup = true;
  engine->getMouseI()->rightClickUp(x, y);
}

void MMouse::middleClickUp(int mousex, int mousey) {
  setxy(mousex, mousey);
  mdown = false;
  mup = true;
  engine->getMouseI()->middleClickUp(x, y);
}

void MMouse::scrollDown(int mousex, int mousey) {
  setxy(mousex, mousey);
  engine->getMouseI()->scrollDown(x, y);
}

void MMouse::scrollUp(int mousex, int mousey) {
  setxy(mousex, mousey);
  engine->getMouseI()->scrollUp(x, y);
}

void MMouse::move(int mousex, int mousey) {
  if(ldown) {
    engine->getMouseI()->mouseDrag(lx, ly, x, y, mousex, mousey);
  } else {
    engine->getMouseI()->mouseMove(x, y, mousex, mousey);
  }
  setxy(mousex, mousey);
}




















