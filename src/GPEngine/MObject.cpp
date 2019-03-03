#include <stdio.h>

#include "MTexture.h"

#include "MObject.h"

using namespace GPE;

MObject::MObject() {
  clip = NULL;
  texture = NULL;
  position = NULL;
}

MObject::~MObject() {
  if(clip != NULL) {
    delete clip;
  }
  if(position != NULL) {
    delete position;
  }
  texture = NULL;
}

void MObject::init(MTexture* _texture, int x, int y) {
  texture = _texture;
  position = {x, y,
    texture->getWidth(), texture->getHeight() };
  clip = NULL;
}

void MObject::init(MTexture* _texture, int x, int y,
  int width, int height)
{
  texture = _texture;
  position = new MRect(x, y, width, height);
  clip = NULL;
}

void MObject::init(MTexture* _texture, int x, int y,
  int clipx, int clipy, int clipw, int cliph)
{
  texture = _texture;
  position = new MRect(x, y,
    texture->getWidth(), texture->getHeight());
  clip = new MRect(clipx, clipy, clipw, cliph);
}

void MObject::init(MTexture* _texture, int x, int y,
  int width, int height, int clipx, int clipy,
  int clipw, int cliph)
{
  texture = _texture;
  position = new MRect(x, y, width, height);
  clip = new MRect(clipx, clipy, clipw, cliph);
}

void MObject::render() {
  texture->render(position->x, position->y, clip, position);
}

