#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "MRect.h"

MRect::MRect() {
  rect = NULL;
}

MRect::MRect(int x, int y, int w, int h) {
  rect = NULL;
  initWH(x, y, w, h);
}

void MRect::close() {
  if(rect != NULL) {
    delete rect;
    rect = NULL;
  }
}

MRect::~MRect() {
  close();
}

void MRect::initWH(int x, int y, int w, int h) {
  close();
  rect = new SDL_Rect();
  rect->x = x;
  rect->y = y;
  rect->w = w;
  rect->h = h;
}

void MRect::init(int x1, int y1, int x2, int y2) {
  initWH(x1, y1, x2-x1, y2-y1);
}

SDL_Rect* MRect::getRect() {
  return rect;
}

