#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "MTexture.h"
#include "MSpriteSheet.h"

using namespace GPE;

GPE::MSpriteSheet::MSpriteSheet() {
  texture = NULL;
  numSprites = 0;
  numSpritesX = 0;
  numSpritesY = 0;
  spriteWidth = 0;
  spriteHeight = 0;
  textureWidth = 0;
  textureHeight = 0;
}

GPE::MSpriteSheet::~MSpriteSheet() {
  free();
}

void GPE::MSpriteSheet::free() {
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

void GPE::MSpriteSheet::init(MTexture* _texture, int x, int y, int ns) {
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
    rects[i] = {(i%numSpritesX)*spriteWidth,
                (i/numSpritesX)*spriteHeight,
                spriteWidth, spriteHeight    };
  }
  if(textureWidth % numSpritesX != 0 ||
     textureHeight % numSpritesY != 0) {
    printf("Uneven sprite size in MSpriteSheet::init\n");
  }
}

void GPE::MSpriteSheet::init(MTexture* _texture, GPRect* _rects, int ns) {
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

void GPE::MSpriteSheet::init(MTexture* _texture, std::vector<GPRect> _rects)
{
  init(_texture, _rects.data(), _rects.size());
}

void GPE::MSpriteSheet::render(int x, int y, int sprite) {
  if(sprite >= numSprites) {
    printf("Sprite %d is out of bounds: %d\n", sprite, numSprites);
  }
  texture->render(x,y,rects[sprite]);
}

void GPE::MSpriteSheet::render(int x, int y, int sprite, int anchorX, int anchorY) {
  if(sprite >= numSprites) {
    printf("Sprite %d is out of bounds: %d\n", sprite, numSprites);
  }
  texture->render(x,y,rects[sprite],anchorX,anchorY);
}

void GPE::MSpriteSheet::renderCentered(int x, int y, int sprite) {
  if(sprite >= numSprites) {
    printf("Sprite %d is out of bounds: %d\n", sprite, numSprites);
  }
  texture->renderCentered(x,y,rects[sprite]);
}

void GPE::MSpriteSheet::renderBottomRight(int x, int y, int sprite) {
  if(sprite >= numSprites) {
    printf("Sprite %d is out of bounds: %d\n", sprite, numSprites);
  }
  texture->renderBottomRight(x,y,rects[sprite]);
}

void GPE::MSpriteSheet::renderBottomleft(int x, int y, int sprite) {
  if(sprite >= numSprites) {
    printf("Sprite %d is out of bounds: %d\n", sprite, numSprites);
  }
  texture->renderBottomLeft(x,y,rects[sprite]);
}

void GPE::MSpriteSheet::renderTopRight(int x, int y, int sprite) {
  if(sprite >= numSprites) {
    printf("Sprite %d is out of bounds: %d\n", sprite, numSprites);
  }
  texture->renderTopRight(x,y,rects[sprite]);
}



void GPE::MSpriteSheet::renderResized(int x, int y, int sprite, GPRect resize) {
  if(sprite >= numSprites) {
    printf("Sprite %d is out of bounds: %d\n", sprite, numSprites);
  }
  texture->renderResized(x,y,rects[sprite],resize);
}

void GPE::MSpriteSheet::renderResized(int x, int y, int sprite, GPRect resize, int anchorX, int anchorY) {
  if(sprite >= numSprites) {
    printf("Sprite %d is out of bounds: %d\n", sprite, numSprites);
  }
  texture->renderResized(x,y,rects[sprite],resize,anchorX,anchorY);
}

void GPE::MSpriteSheet::renderResizedCentered(int x, int y, int sprite, GPRect resize) {
  if(sprite >= numSprites) {
    printf("Sprite %d is out of bounds: %d\n", sprite, numSprites);
  }
  texture->renderResizedCentered(x,y,rects[sprite],resize);
}

void GPE::MSpriteSheet::renderResizedBottomRight(int x, int y, int sprite, GPRect resize) {
  if(sprite >= numSprites) {
    printf("Sprite %d is out of bounds: %d\n", sprite, numSprites);
  }
  texture->renderResizedBottomRight(x,y,rects[sprite],resize);
}

void GPE::MSpriteSheet::renderResizedBottomleft(int x, int y, int sprite, GPRect resize) {
  if(sprite >= numSprites) {
    printf("Sprite %d is out of bounds: %d\n", sprite, numSprites);
  }
  texture->renderResizedBottomLeft(x,y,rects[sprite],resize);
}

void GPE::MSpriteSheet::renderResizedTopRight(int x, int y, int sprite, GPRect resize) {
  if(sprite >= numSprites) {
    printf("Sprite %d is out of bounds: %d\n", sprite, numSprites);
  }
  texture->renderResizedTopRight(x,y,rects[sprite],resize);
}

int GPE::MSpriteSheet::getWidth() {
  return textureWidth;
}

int GPE::MSpriteSheet::getWidth(int sprite) {
  return rects[sprite].w;
}

int GPE::MSpriteSheet::getHeight() {
  return textureHeight;
}

int GPE::MSpriteSheet::getHeight(int sprite) {
  return rects[sprite].h;
}

int GPE::MSpriteSheet::getNumSprites() {
  return numSprites;
}

GPE::MSpriteSheet* GPE::create_spritesheet(MTexture* texture, int x, int y, int ns) {
  GPE::MSpriteSheet *tmp = new GPE::MSpriteSheet();
  tmp->init(texture, x, y, ns);
  return tmp;
}

GPE::MSpriteSheet* GPE::create_spritesheet(MTexture* texture, GPRect* rects, int ns) {
  GPE::MSpriteSheet *tmp = new GPE::MSpriteSheet();
  tmp->init(texture, rects, ns);
  return tmp;
}

GPE::MSpriteSheet* GPE::create_spritesheet(MTexture* texture, std::vector<GPRect> rects) {
  GPE::MSpriteSheet *tmp = new GPE::MSpriteSheet();
  tmp->init(texture, rects);
  return tmp;
}

