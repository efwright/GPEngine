#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "MWindow.h"
#include "MTexture.h"
#include "MEngine.h"

MWindow::MWindow() {
  window = NULL;
  renderer = NULL;
  width = 1366;
  height = 768;
  vsync = false;
  fullscreen = false;
  ratio = 1.0;
}

MWindow::~MWindow() { /* Nothing so far */ }

void MWindow::setVsync(bool b) {
  vsync = b;
}

void MWindow::resizeRatio(int w, int h) {
  SDL_SetWindowSize(window, w, (int) (((double) w) * ratio) );
}

bool MWindow::init(std::string name, int resX, int resY, bool v,
 bool fs) {
  bool success = true;
  vsync = v;
  fullscreen = fs;
  width = resX; height = resY;
  Uint32 _fullscreen;
  if(fs) _fullscreen = SDL_WINDOW_FULLSCREEN;
   else  _fullscreen = 0;
  window = SDL_CreateWindow(name.c_str(), 
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
    width, height,
    SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE | _fullscreen);
  SDL_SetWindowMinimumSize(window, width, height);
  screenWidth = width;
  screenHeight = height;
  ratio = ((double) height) / ((double) width);
  if( window == NULL ) {
    printf( "Window could not be created! SDL_Error: %s\n",
      SDL_GetError() );
    success = false;
  } else {
    gSDLWindow = window;
    Uint32 _vsync;
    if(v) _vsync = SDL_RENDERER_PRESENTVSYNC;
     else  _vsync = 0;
    renderer = SDL_CreateRenderer( window, -1,
      SDL_RENDERER_ACCELERATED | _vsync); 
    if( renderer == NULL ) { 
      printf( "Renderer could not be created! SDL Error: %s\n",
        SDL_GetError() ); 
      success = false; 
    } else { 
      SDL_RenderSetLogicalSize(renderer, width, height);
      SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0xFF );
      gSDLRenderer = renderer;
    }
  }
  return success;
}

void MWindow::show() {
  SDL_ShowWindow(window);
}

void MWindow::close() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window); 
  window = NULL; 
  renderer = NULL;
  Mix_Quit();
  IMG_Quit();
  SDL_Quit(); 
}

SDL_Renderer* MWindow::getRenderer() {
  return renderer;
}

void MWindow::clear() {
  SDL_RenderClear(renderer);
}

void MWindow::draw() {
  SDL_RenderPresent(renderer);
}

int MWindow::getWidth() {
  return width;
}

int MWindow::getHeight() {
  return height;
}

