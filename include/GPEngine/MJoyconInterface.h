#ifndef MJOYCONINTERFACE_HEADER
#define MJOYCONINTERFACE_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "MJoycon.h"

class MJoycon;

class MJoyconInterface {
  public:
    virtual void initJoycon(MJoycon*) {};
    virtual void joyconX(int x, int joycon) {};
    virtual void joyconY(int y, int joycon) {};
    virtual void joyconRX(int x, int joycon) {};
    virtual void joyconRY(int y, int joycon) {};
    virtual void buttonPress(int button, int joycon) {};
    virtual void buttonRelease(int button, int joycon) {};
  private:
};

#endif
