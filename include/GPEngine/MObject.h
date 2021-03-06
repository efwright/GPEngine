#ifndef MOBJECT_HEADER
#define MOBJECT_HEADER

#include <stdio.h>

#include "MTexture.h"
#include "MRect.h"

//! Give a physical, easy to draw rectangle to a texture

class MObject {
  public:
    MObject();
    ~MObject();
    void init(MTexture* _texture, int x, int y);
    void init(MTexture* _texture, int x, int y,
      int width, int height);
    void init(MTexture* _texture, int x, int y,
      int clipx, int clipy, int clipw, int cliph);
    void init(MTexture* _texture, int x, int y,
      int width, int height, int clipx, int clipy,
      int clipw, int cliph);
    void render();
  protected:
    MRect* clip;
    MTexture* texture;
    MRect* position;
};

#endif
