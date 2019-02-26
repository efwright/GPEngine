#ifndef MJOYCON_HEADER
#define MJOYCON_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "MGame.h"
#include "MEngine.h"
#include "MJoyconInterface.h"

/*********************************************************************
  MJoycon:
  Joystick ranges from -32768 -> 32767
  SDL_NumJoysticks()
  e->type SDL_JOYAXISMOTION
  e->jaxis.which = joycon number
  e->jaxis.axis == 0 x-axis, y otherwise
  0 = lx, 1 = ly, 3 = rx, 4 = ry
  e->jaxis.value the amount moved

  e->type SDL_JOYBUTTONDOWN or SDL_JOYBUTTONUP
  e->jbutton.button
  e->jbutton.state either SDL_PRESSED or SDL_RELEASED
  e->jbutton.which which joycon

  Author: Eric
 *********************************************************************/

// TODO add MGame* and create interface with it. Should have methods
// for moving the joystick (I'm not sure what to do with controllers
// that have two joysticks?), and an interface for buttons.

class MJoyconInterface;

class MJoycon {
  public:
    MJoycon();
    ~MJoycon();
    bool init();
    bool init(int);
    void close();
    int getNum();
    void moveLeftX(int x);
    void moveLeftY(int y);
    void moveRightX(int x);
    void moveRightY(int y);
    int getNumButtons();
  private:
    SDL_Joystick* joystick;
    const int JOYSTICK_DEAD_ZONE = 8000;
    void free();
    int joyconNum;
    int numButtons;
};

int getNumJoysticks();

#endif
