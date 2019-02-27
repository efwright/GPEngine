#ifndef MSPRITESHEET_HEADER
#define MSPRITESHEET_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

#include "MTexture.h"
#include "MRect.h"

//! Organize MTexture as a group of sprites


namespace GPE
{

class MSpriteSheet;
MSpriteSheet* create_spritesheet(GPE::MTexture*, int, int, int);
MSpriteSheet* create_spritesheet(GPE::MTexture*, MRect*, int);
MSpriteSheet* create_spritesheet(GPE::MTexture*, std::vector<MRect>);

class MSpriteSheet {
  protected:
    MSpriteSheet();
    ~MSpriteSheet();
    virtual void init(MTexture* texture, int x, int y, int ns);
    virtual void init(MTexture* texture, MRect*, int);
    virtual void init(MTexture* texture, std::vector<MRect>);
  public:
    virtual void render( int x, int y,
      int sprite, MRect* resize = NULL);
    virtual void renderCentered( int x, int y,
      int sprite, MRect* resize = NULL);
    virtual void renderBottomLeft( int x, int y,
      int sprite, MRect* resize = NULL);
    virtual void renderBottomRight( int x, int y,
      int sprite, MRect* resize = NULL);
    virtual void renderTopRight( int x, int y,
      int sprite, MRect* resize = NULL);
    virtual void render( int x, int y,
      int anchorX, int anchorY, int sprite, MRect* resize = NULL);
    virtual void renderAnchored( int x, int y,
      int anchorX, int anchorY, int sprite, MRect* resize = NULL);


    virtual int getWidth();
    virtual int getWidth(int sprite);
    virtual int getHeight();
    virtual int getHeight(int sprite);
    virtual int getNumSprites();
  protected:
    MTexture* texture;
    int numSprites;
    std::vector<MRect> rects;
    int numSpritesX;
    int numSpritesY;
    int spriteWidth;
    int spriteHeight;
    int textureWidth;
    int textureHeight;
    virtual void free();

  public:
    friend MSpriteSheet* create_spritesheet(MTexture*, int, int, int);
    friend MSpriteSheet* create_spritesheet(MTexture*, MRect*, int);
    friend MSpriteSheet* create_spritesheet(MTexture*, std::vector<MRect>);
      
};

}

#endif

