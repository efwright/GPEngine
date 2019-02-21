#ifndef MLARGESPRITESHEET_HEADER
#define MLARGESPRITESHEET_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

#include "MTexture.h"
#include "MRect.h"

#include "MSpriteSheet.h"

//! Sprite sheet that can hold multiple textures

class MLargeSpriteSheet : public MSpriteSheet {
  public:
    MLargeSpriteSheet();
    ~MLargeSpriteSheet();
    void init(MTexture** textures, int numTextures, int x, int y,
      int ns);
    void init(MTexture* texture, int x, int y, int ns) override;
    void init(MTexture* texture, MRect*, int) override;
    void init(MTexture* texture, std::vector<MRect>) override;
    void render( int x, int y,
      int sprite, MRect* resize = NULL) override;
    void renderCentered( int x, int y,
      int sprite, MRect* resize = NULL) override;
    void renderBottomLeft( int x, int y,
      int sprite, MRect* resize = NULL) override;
    void renderBottomRight( int x, int y,
      int sprite, MRect* resize = NULL) override;
    void renderTopRight( int x, int y,
      int sprite, MRect* resize = NULL) override;
    void render( int x, int y,
      int anchorX, int anchorY, int sprite, MRect* resize = NULL)
        override;
    void renderAnchored( int x, int y,
      int anchorX, int anchorY, int sprite, MRect* resize = NULL)
        override;


    int getWidth() override;
    int getWidth(int sprite) override;
    int getHeight() override;
    int getHeight(int sprite) override;
    int getNumSprites() override;
  protected:
    void free() override;
    std::vector<MTexture*> textures;
    int spritesPerSheet;

};

#endif
