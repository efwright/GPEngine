#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "MTexture.h"
#include "MSpriteSheet.h"
#include "MRect.h"
#include "MWindow.h"

MSpriteSheet::MSpriteSheet() {
  texture = NULL;
  numSprites = 0;
  numSpritesX = 0;
  numSpritesY = 0;
  spriteWidth = 0;
  spriteHeight = 0;
  textureWidth = 0;
  textureHeight = 0;
}

MSpriteSheet::~MSpriteSheet() {
  free();
}

void MSpriteSheet::free() {
  texture = NULL;
  numSprites = 0;
  numSpritesX = 0;
  numSpritesY = 0;
  spriteWidth = 0;
  spriteHeight = 0;
  textureWidth = 0;
  textureHeight = 0;
  rects.clear();
}

void MSpriteSheet::init(MTexture* _texture, int x, int y, int ns) {
  free();
  texture = _texture;
  numSprites = ns;
  numSpritesX = x;
  numSpritesY = y;
  textureWidth = texture->getWidth();
  textureHeight = texture->getHeight();
  spriteWidth = textureWidth / numSpritesX;
  spriteHeight = textureHeight / numSpritesY;
  rects.resize(numSprites);
  for(int i = 0; i < numSprites; i++) {
    rects[i] = MRect((i%numSpritesX)*spriteWidth,
                     (i/numSpritesX)*spriteHeight,
                     spriteWidth, spriteHeight);
  }
  if(textureWidth % numSpritesX != 0 ||
     textureHeight % numSpritesY != 0) {
    printf("Uneven sprite size in MSpriteSheet::init\n");
  }
}

void MSpriteSheet::init(MTexture* _texture, MRect* _rects, int ns) {
  free();
  texture = _texture;
  numSprites = ns;
  numSpritesX = 0;
  numSpritesY = 0;
  textureWidth = texture->getWidth();
  textureHeight = texture->getHeight();
  spriteWidth = 0;
  spriteHeight = 0;
  rects.resize(numSprites);
  for(int i = 0; i < numSprites; i++) {
    rects[i] = _rects[i];
  }
  if(textureWidth % numSpritesX != 0 ||
     textureHeight % numSpritesY != 0) {
    printf("Uneven sprite size in MSpriteSheet::init\n");
  }
}

void MSpriteSheet::init(MTexture* _texture, std::vector<MRect> _rects)
{
  init(_texture, _rects.data(), _rects.size());
}

void MSpriteSheet::render( int x, int y,
                          int sprite, MRect* resize) 
{
  if(sprite >= numSprites) {
    printf("Sprite %d is out of bounds: %d\n", sprite, numSprites);
  }
  texture->render( x, y, &rects[sprite], resize);
} 

void MSpriteSheet::renderCentered( int x, int y,
                          int sprite, MRect* resize) 
{
  if(sprite >= numSprites) {
    printf("Sprite %d is out of bounds: %d\n", sprite, numSprites);
  }
  texture->renderCentered( x, y, &rects[sprite], resize);
} 

void MSpriteSheet::renderBottomLeft( int x, int y,
                          int sprite, MRect* resize) 
{
  if(sprite >= numSprites) {
    printf("Sprite %d is out of bounds: %d\n", sprite, numSprites);
  }
  texture->renderBottomLeft( x, y, &rects[sprite], resize);
} 

void MSpriteSheet::renderBottomRight( int x, int y,
                          int sprite, MRect* resize) 
{
  if(sprite >= numSprites) {
    printf("Sprite %d is out of bounds: %d\n", sprite, numSprites);
  }
  texture->renderBottomRight( x, y, &rects[sprite], resize);
} 

void MSpriteSheet::renderTopRight( int x, int y,
                          int sprite, MRect* resize) 
{
  if(sprite >= numSprites) {
    printf("Sprite %d is out of bounds: %d\n", sprite, numSprites);
  }
  texture->renderTopRight( x, y, &rects[sprite], resize);
} 

void MSpriteSheet::render( int x, int y,
                          int anchorX, int anchorY,
                          int sprite, MRect* resize) 
{
  if(sprite >= numSprites) {
    printf("Sprite %d is out of bounds: %d\n", sprite, numSprites);
  }
  texture->render( x, y, anchorX, anchorY, 
                          &rects[sprite], resize);
} 

void MSpriteSheet::renderAnchored( int x, int y,
                          int anchorX, int anchorY,
                          int sprite, MRect* resize) 
{
  if(sprite >= numSprites) {
    printf("Sprite %d is out of bounds: %d\n", sprite, numSprites);
  }
  texture->renderAnchored( x, y, anchorX, anchorY, 
                          &rects[sprite], resize);
} 

int MSpriteSheet::getWidth() {
  return textureWidth;
}

int MSpriteSheet::getWidth(int sprite) {
  return rects[sprite].w;
}

int MSpriteSheet::getHeight() {
  return textureHeight;
}

int MSpriteSheet::getHeight(int sprite) {
  return rects[sprite].h;
}

int MSpriteSheet::getNumSprites() {
  return numSprites;
}

