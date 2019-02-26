#ifndef MMOUSEINTERFACE_HEADER
#define MMOUSEINTERFACE_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string>

class MMouseInterface {
  public:
    virtual void init(){};
    virtual void leftClickDown(int x, int y) {};
    virtual void rightClickDown(int x, int y) {};
    virtual void middleClickDown(int x, int y) {};
    virtual void leftClickUp(int x, int y) {};
    virtual void rightClickUp(int x, int y) {};
    virtual void middleClickUp(int x, int y) {};
    virtual void mouseDrag(int startx, int starty, int oldx,
      int oldy, int newx, int newy) {};
    virtual void mouseMove(int oldx, int oldy, int newx, int newy) {};
    virtual void scrollDown(int x, int y) {};
    virtual void scrollUp(int x, int y) {};
};

#endif
