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
MSpriteSheet* create_spritesheet(GPE::MTexture*, GPRect*, int);
MSpriteSheet* create_spritesheet(GPE::MTexture*, std::vector<GPRect>);

class MSpriteSheet {
  protected:
    MSpriteSheet();
    ~MSpriteSheet();
    void init(MTexture* texture, int x, int y, int ns);
    void init(MTexture* texture, GPRect*, int);
    void init(MTexture* texture, std::vector<GPRect>);
  public:

    void render(int x, int y, int sprite);
    void render(int x, int y, int sprite, int anchorX, int anchorY);
    void renderCentered(int x, int y, int sprite);
    void renderBottomRight(int x, int y, int sprite);
    void renderBottomleft(int x, int y, int sprite);
    void renderTopRight(int x, int y, int sprite);

    void renderResized(int x, int y, int sprite, GPRect resize);
    void renderResized(int x, int y, int sprite, GPRect resize, int anchorX, int anchorY);
    void renderResizedCentered(int x, int y, int sprite, GPRect resize);
    void renderResizedBottomRight(int x, int y, int sprite, GPRect resize);
    void renderResizedBottomleft(int x, int y, int sprite, GPRect resize);
    void renderResizedTopRight(int x, int y, int sprite, GPRect resize);

    int getWidth();
    int getWidth(int sprite);
    int getHeight();
    int getHeight(int sprite);
    int getNumSprites();
  protected:
    MTexture* texture;
    int numSprites;
    std::vector<GPRect> rects;
    int numSpritesX;
    int numSpritesY;
    int spriteWidth;
    int spriteHeight;
    int textureWidth;
    int textureHeight;
    void free();

  public:
    friend MSpriteSheet* create_spritesheet(MTexture*, int, int, int);
    friend MSpriteSheet* create_spritesheet(MTexture*, GPRect*, int);
    friend MSpriteSheet* create_spritesheet(MTexture*, std::vector<GPRect>);
      
};

}

#endif

