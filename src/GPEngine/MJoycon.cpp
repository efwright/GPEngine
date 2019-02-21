#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "MJoycon.h"
#include "MGame.h"
#include "MEngine.h"
#include "MJoyconInterface.h"

MJoycon::MJoycon() {
  joystick = NULL;
  joyconNum = 0;
  numButtons = 0;
}

MJoycon::~MJoycon() {
  free();
}

bool MJoycon::init(MEngine* e) {
  return init(e, 0);
}

bool MJoycon::init(MEngine* e, int j) {
  free();
  joystick = SDL_JoystickOpen(j);
  if(joystick == NULL) {
    printf("Warning: Unable to open game controller! SDL Error: %s\n",
      SDL_GetError());
  } else {
    joyconNum = j;
    engine = e;
    numButtons = SDL_JoystickNumButtons(joystick);
  }
  return joystick != NULL;
}

void MJoycon::free() {
  if(joystick != NULL) {
    SDL_JoystickClose(joystick);
    joystick = NULL;
  }
  joyconNum = 0;
  numButtons = 0;
  engine = NULL;
}

void MJoycon::close() {
  free();
}

int MJoycon::getNum() {
  return joyconNum;
}

void MJoycon::moveLeftX(int x) {
  if(abs(x)-JOYSTICK_DEAD_ZONE) {
    engine->getJoyconI()->joyconX(x, joyconNum);
  }
}

void MJoycon::moveLeftY(int y) {
  if(abs(y)-JOYSTICK_DEAD_ZONE) {
    engine->getJoyconI()->joyconY(y, joyconNum);
  }
}

void MJoycon::moveRightX(int x) {
  if(abs(x)-JOYSTICK_DEAD_ZONE) {
    engine->getJoyconI()->joyconRX(x, joyconNum);
  }
}

void MJoycon::moveRightY(int y) {
  if(abs(y)-JOYSTICK_DEAD_ZONE) {
    engine->getJoyconI()->joyconRY(y, joyconNum);
  }
}

int MJoycon::getNumButtons() {
  return numButtons;
}

int getNumJoysticks() {
  return SDL_NumJoysticks();
}

