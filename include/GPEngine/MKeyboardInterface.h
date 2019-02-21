#ifndef MKEYBOARDINTERFACE_HEADER
#define MKEYBOARDINTERFACE_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string>

class MKeyboard;

class MKeyboardInterface {
  public:
    MKeyboardInterface() { keyboard = NULL; };
    virtual void keyPress(int key) {};
    virtual void keyRelease(int key) {};
    virtual void updateKeyStates() {
      keyStates = SDL_GetKeyboardState(NULL);
    }
  protected:
    MKeyboard* keyboard;
    const Uint8* keyStates;
};

#endif
