#ifndef MROOM_HEADER
#define MROOM_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

//! A Room contains updateable and drawable objects with several environment variables (e.g gravity)
/*!
 *  A Room is meant to simplify the process of managing objects in a game enviroment. The
 *  Room provides an interface for updating and drawing objects within the room
 *  automatically with the Engine. You can have multiple rooms, and you can update
 *  all of them. However, only one room should be drawn at a time. A room should also
 *  take up the entire drawable screen.
 *
 *  The room stores objects in non thread-safe vectors. Any updates to the vectors
 *  should occur during the lowUpdate, and drawing from the vectors occur during
 *  the Engine draw. These vectors should not be written to (they can be read from)
 *  during the highUpdate.
 */

class MRoom : public MGame {
  public:
  private:
};

#endif

