#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

#include "MTexture.h"
#include "MSpriteSheet.h"
#include "MRect.h"

#include "MLargeSpriteSheet.h"

MLargeSpriteSheet::MLargeSpriteSheet() {
  textures.clear();
  spritesPerSheet = 0;
}

MLargeSpriteSheet::~MLargeSpriteSheet() {
  free();
}

void MLargeSpriteSheet::free() {
  MSpriteSheet::free();
  textures.clear();
  spritesPerSheet = 0;
}

void MLargeSpriteSheet::init(MTexture** _textures, int numTextures,
  int x, int y, int ns)
{
  free();
  texture = _textures[0];
  numSprites = ns;
  numSpritesX = x;
  numSpritesY = y;
  textureWidth = texture->getWidth();
  textureHeight = texture->getHeight();
  spriteWidth = textureWidth / numSpritesX;
  spriteHeight = textureHeight / numSpritesY;
  rects.resize(numSprites);
  spritesPerSheet = numSpritesX * numSpritesY;
  textures.resize(numTextures);
  for(int i = 0; i < numSprites; i++) {
    rects[i] = MRect((i%numSpritesX)*spriteWidth,
                     ((i%spritesPerSheet)/numSpritesX)*spriteHeight,
                     spriteWidth, spriteHeight);
  }
  for(int i = 0; i < numTextures; i++) {
    textures[i] = _textures[i];
  }
}

void MLargeSpriteSheet::init(MTexture* _texture, int x, int y, int ns) {
  free();
  printf("For LargeSpriteSheets use init(MTexture**, numTextures, x, y, numSprites\n");
}

void MLargeSpriteSheet::init(MTexture* _texture, MRect* _rects, int ns) {
  free();
  printf("For LargeSpriteSheets use init(MTexture**, numTextures, x, y, numSprites\n");
}

void MLargeSpriteSheet::init(MTexture* _texture, std::vector<MRect> _rects)
{
  free();
  printf("For LargeSpriteSheets use init(MTexture**, numTextures, x, y, numSprites\n");
}

void MLargeSpriteSheet::render( int x, int y,
                          int sprite, MRect* resize) 
{
  if(sprite >= numSprites) {
    printf("Sprite %d is out of bounds: %d\n", sprite, numSprites);
  }
  textures[sprite/spritesPerSheet]->render( x, y,
    &rects[sprite], resize);
} 

void MLargeSpriteSheet::renderCentered( int x, int y,
                          int sprite, MRect* resize) 
{
  if(sprite >= numSprites) {
    printf("Sprite %d is out of bounds: %d\n", sprite, numSprites);
  }
  textures[sprite/spritesPerSheet]->renderCentered( x, y,
    &rects[sprite], resize);
} 

void MLargeSpriteSheet::renderBottomLeft( int x, int y,
                          int sprite, MRect* resize) 
{
  if(sprite >= numSprites) {
    printf("Sprite %d is out of bounds: %d\n", sprite, numSprites);
  }
  textures[sprite/spritesPerSheet]->renderBottomLeft( x, y,
    &rects[sprite], resize);
} 

void MLargeSpriteSheet::renderBottomRight( int x,
  int y, int sprite, MRect* resize) 
{
  if(sprite >= numSprites) {
    printf("Sprite %d is out of bounds: %d\n", sprite, numSprites);
  }
  textures[sprite/spritesPerSheet]->renderBottomRight( x, y,
    &rects[sprite], resize);
} 

void MLargeSpriteSheet::renderTopRight( int x, int y,
                          int sprite, MRect* resize) 
{
  if(sprite >= numSprites) {
    printf("Sprite %d is out of bounds: %d\n", sprite, numSprites);
  }
  textures[sprite/spritesPerSheet]->renderTopRight( x, y,
    &rects[sprite], resize);
} 

void MLargeSpriteSheet::render( int x, int y,
                          int anchorX, int anchorY,
                          int sprite, MRect* resize) 
{
  if(sprite >= numSprites) {
    printf("Sprite %d is out of bounds: %d\n", sprite, numSprites);
  }
  textures[sprite/spritesPerSheet]->render( x, y, anchorX,
    anchorY, &rects[sprite], resize);
} 

void MLargeSpriteSheet::renderAnchored( int x, int y,
                          int anchorX, int anchorY,
                          int sprite, MRect* resize) 
{
  if(sprite >= numSprites) {
    printf("Sprite %d is out of bounds: %d\n", sprite, numSprites);
  }
  textures[sprite/spritesPerSheet]->renderAnchored( x, y,
    anchorX, anchorY, &rects[sprite], resize);
} 

int MLargeSpriteSheet::getWidth() {
  return textureWidth;
}

int MLargeSpriteSheet::getWidth(int sprite) {
  return rects[sprite].w;
}

int MLargeSpriteSheet::getHeight() {
  return textureHeight;
}

int MLargeSpriteSheet::getHeight(int sprite) {
  return rects[sprite].h;
}

int MLargeSpriteSheet::getNumSprites() {
  return numSprites;
}

