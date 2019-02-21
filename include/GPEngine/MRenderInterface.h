#ifndef MRENDERINTERFACE_HEADER
#define MRENDERINTERFACE_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "MWindow.h"

class MRenderInterface {
  public:
    virtual void init() {};
    virtual void render() {};
  private:
};

#endif
