#ifndef MGAME_HEADER
#define MGAME_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "MMouseInterface.h"
#include "MJoyconInterface.h"
#include "MRenderInterface.h"
#include "MKeyboardInterface.h"

/*********************************************************************
  MGame:
   Meant to be overridden to accomodate internal game structure. An
   MGame functions as all necessary I/O interfaces, however, it is
   possible to use other interfaces instead of the MGame.
   MEngine will only have one of each interface at any given time,
   and only one MGame at a time.
   MGame will be initialized with screen resolution to be able to
   adjust game logic.

  Author: Eric
 *********************************************************************/

class MGame : public MMouseInterface, public MJoyconInterface, public MRenderInterface, public MKeyboardInterface {
  public:
    virtual void init(int, int, unsigned int) {};
    virtual void update(long) {};
    virtual void updateThreaded(long) {};
    virtual void quit() {};
  private:
};

#endif
