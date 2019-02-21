#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <algorithm>

#include "MSpriteSheet.h"
#include "MAnimation.h"

MAnimation::MAnimation() {
  spriteSheet = NULL;
  numSprites = 0;
  FPS = 60;
  FPMS = 1000/FPS;
  currentSprite = 0;
  currentTime = 0;
  spriteOrder.clear();
}

MAnimation::~MAnimation() { 
  spriteSheet = NULL;
  numSprites = 0;
  currentSprite = 0;
  currentTime = 0;
  spriteOrder.clear();
}

void MAnimation::init(MSpriteSheet* ss, int fps) {
  FPS = fps;
  FPMS = 1000/((long) FPS);
  numSprites = ss->getNumSprites();
  spriteOrder.resize(numSprites);
  for(int i = 0; i < numSprites; i++) {
    spriteOrder[i] = i;
  }
  spriteSheet = ss;
  currentSprite = 0;
  currentTime = 0;
}

void MAnimation::init(MSpriteSheet* ss, int fps, std::vector<int> so) {
  FPS = fps;
  FPMS = 1000/((long) FPS);
  numSprites = so.size();
  spriteOrder.resize(numSprites);
  for(int i = 0; i < numSprites; i++) {
    spriteOrder[i] = so[i];
  }
  spriteSheet = ss;
  currentSprite = 0;
  currentTime = 0;
}

void MAnimation::init(MSpriteSheet* ss, int fps, int start, int end) { // end inclusive
  FPS = fps;
  FPMS = 1000/((long) FPS);
  numSprites = end-start+1;
  spriteOrder.resize(numSprites);
  for(int i = 0; i < numSprites; i++) {
    spriteOrder[i] = start+i;
  }
  spriteSheet = ss;
  currentSprite = 0;
  currentTime = 0;
}

void MAnimation::render( int x, int y) {
  spriteSheet->render( x, y, spriteOrder[currentSprite]);
}

void MAnimation::renderCentered( int x, int y) {
  spriteSheet->renderCentered( x, y, spriteOrder[currentSprite]);
}

void MAnimation::renderBottomRight( int x, int y) {
  spriteSheet->renderBottomRight( x, y, spriteOrder[currentSprite]);
}

void MAnimation::update() {
  currentSprite = (currentSprite+1) % numSprites;
}

void MAnimation::update(long et) {
  currentTime += et;
  if(currentTime >= FPMS) {
    currentTime = currentTime % FPMS;
    currentSprite = (currentSprite+1) % numSprites;
  }
}

void MAnimation::updateNoRepeat(long et) {
  currentTime += et;
  if(currentTime >= FPMS) {
    currentTime = currentTime % FPMS;
    currentSprite = std::max(currentSprite,
                        (currentSprite+1)%numSprites);
  }
}

void MAnimation::update(long et, bool repeat) {
  if(repeat) {
    update(et);
  } else {
    updateNoRepeat(et);
  }
}

