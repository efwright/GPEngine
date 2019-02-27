#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_net.h>

#include "MGame.h"
#include "MKeyboardInterface.h"
#include "MMouseInterface.h"
#include "MJoyconInterface.h"
#include "MRenderInterface.h"

#include "MEngine.h"

using namespace GPE;

// Initialization
void init_IMG_TTF_MIX_NET();
void initInterfaces(MRenderInterface*, MMouseInterface*, 
  MJoyconInterface*, MKeyboardInterface*, MGame*);
void initSound();

// Window
void initWindow();
namespace GPE
{
  SDL_Window* gWindow;
  SDL_Renderer* gRenderer;
}

// Settings
void initSettings(std::string);
void loadDefaultSettings();
namespace GPE
{
  int screenWidth;
  int screenHeight;
  bool vsync;
  bool fullscreen;
  bool resizeable;
  Uint32 FPS;
  Uint32 MS_delay;
  std::string name;
  Uint32 maxEvents;
  int musicVolume;
  int soundVolume;
}

// Mouse
void initMouse();
int x, y;
int lx, ly;
int px, py;
bool ldown, rdown, mdown;

// Renderthread
void initRenderthread();
int renderThreadFunc(void*);
SDL_cond* renderStart;
SDL_cond* renderFinished;
SDL_mutex* renderLock;
SDL_mutex* engineLock;
SDL_Thread* renderThread;

// Events
void handleEvent(SDL_Event);
bool handleQuit(SDL_Event);
bool handleMouse(SDL_Event);
bool handleKeyboard(SDL_Event);
bool handleJoycon(SDL_Event);

// Run
void start_1thread_drawthread();
bool running;
bool shutdown;
MRenderInterface* renderI;
MMouseInterface* mouseI;
MKeyboardInterface* keyboardI;
MJoyconInterface* joyconI;
MGame* game;
Uint32 ut, et, st;

//////////////////////////////////
void GPE::Engine_Init(std::string name, std::string settings,
 MRenderInterface* ri, MMouseInterface* mi, MJoyconInterface* ji,
 MKeyboardInterface* ki, MGame* g) {
  initSettings(settings);
  initWindow();
  init_IMG_TTF_MIX_NET();
  initSound();
  initMouse();
  initInterfaces(ri, mi, ji, ki, g);
}

void GPE::Engine_Finalize() {
  SDL_DestroyRenderer(gRenderer);
  SDL_DestroyWindow(gWindow);
  SDLNet_Quit();
  TTF_Quit();
  IMG_Quit();
  Mix_Quit();
  SDL_Quit();
}

void GPE::Engine_Start() {
  start_1thread_drawthread();
}

void GPE::Engine_swapMouse(MMouseInterface* mi) {
  mouseI = mi;
}

void GPE::Engine_swapKeyboard(MKeyboardInterface* ki) {
  keyboardI = ki;
}

void GPE::Engine_swapJoycon(MJoyconInterface* ji) {
  joyconI = ji;
}

void GPE::Engine_swapRenderer(MRenderInterface* ri) {
  renderI = ri;
}

void GPE::Engine_swapGame(MGame* g) {
  game = g;
}

void GPE::Engine_endGame() {
  shutdown = true;
}

void GPE::Engine_pause() { }

void GPE::Engine_pauseUpdate() { }

void GPE::Engine_pauseDraw() { }

void GPE::Engine_unpause() { }

void GPE::Engine_unpauseUpdate() { }

void GPE::Engine_unpauseDraw() { }

void initWindow() {
  // Get flags based on settings
  Uint32 windowFlags = 0;
  Uint32 rendererFlags = 0;
  if(fullscreen) windowFlags = windowFlags | SDL_WINDOW_FULLSCREEN;
  if(resizeable) windowFlags = windowFlags | SDL_WINDOW_RESIZABLE;
  windowFlags = windowFlags | SDL_WINDOW_HIDDEN;
  if(vsync) rendererFlags = rendererFlags | SDL_RENDERER_PRESENTVSYNC;
  rendererFlags = rendererFlags | SDL_RENDERER_ACCELERATED;

  // Initialize SDL
  if( SDL_Init( SDL_INIT_VIDEO    | 
                SDL_INIT_JOYSTICK | 
                SDL_INIT_AUDIO      ) < 0 ) { 
    printf( "Could not initialize engine: %s\n", SDL_GetError() );
    exit(-1);
  }

  // Create a new window
  gWindow = SDL_CreateWindow(name.c_str(),
   SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
   screenWidth, screenHeight, windowFlags);
  if(gWindow == NULL) {
    printf("Window could not be created: %s\n", SDL_GetError());
    exit(-1);
  }
  //SDL_SetWindowMinimumSize(gWindow, screenWidth, screenHeight);

  // Create a new renderer
  gRenderer = SDL_CreateRenderer(gWindow, -1, rendererFlags);
  if(gRenderer == NULL) {
    printf("Renderer could not be created: %s\n", SDL_GetError());
    exit(-1);
  }
}

void init_IMG_TTF_MIX_NET() {
  if( !( IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG ) ) { 
    printf("Engine could not be initialized: %s\n", IMG_GetError() ); 
    exit(-1);
  } 
  if(TTF_Init() < 0) {
    printf( "Engine could not be initialized: %s\n", TTF_GetError() ); 
    exit(-1);
  }
  if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0 ) { 
    printf("Engine could not be initialized: %s\n", Mix_GetError()); 
    exit(-1);
  }
  if(SDLNet_Init() < 0) {
    printf("Engine could not be initialized: %s\n", SDLNet_GetError());
    exit(-1);
  }
}

void initInterfaces(MRenderInterface* ri, MMouseInterface* mi, 
  MJoyconInterface* ji, MKeyboardInterface* ki, MGame* g) {

  renderI = ri;
  mouseI = mi;
  joyconI = ji;
  keyboardI = ki;
  game = g;

  renderI->initRender(screenWidth, screenHeight, FPS);
  mouseI->init();
  joyconI->init();
  keyboardI->init();
  game->initGame(screenWidth, screenHeight, FPS);
}

void initSettings(std::string settings) {
  loadDefaultSettings();
}

void loadDefaultSettings() {
  screenWidth = 800;
  screenHeight = 600;
  vsync = true;
  fullscreen = false;
  resizeable = false;
  FPS = 60;
  MS_delay = 1000/FPS;
  name = "GPEngine";
  maxEvents = 100;
  musicVolume = 128;
  soundVolume = 128;
}

void initSound() {
  Mix_VolumeMusic(musicVolume);
  Mix_Volume(-1, soundVolume);
}

void initMouse() {
  x = 0; y = 0;
  lx = 0; ly = 0;
  px = 0; py = 0;
  ldown = false;
  rdown = false;
  mdown = false;
}

void initRenderthread() {
  renderStart = SDL_CreateCond();
  renderFinished = SDL_CreateCond();
  renderLock = SDL_CreateMutex();
  engineLock = SDL_CreateMutex();
  SDL_LockMutex(engineLock);
  renderThread = SDL_CreateThread(renderThreadFunc,
   "RenderThread", NULL);
}

int renderThreadFunc(void* data) {
  SDL_LockMutex(renderLock);
  do {
    SDL_CondWait(renderStart, renderLock);
    SDL_RenderClear(gRenderer);
    renderI->render(ut);

    SDL_LockMutex(engineLock);
    SDL_CondSignal(renderFinished);
    SDL_UnlockMutex(engineLock);
  } while(running);
  SDL_UnlockMutex(renderLock);
  return 0;
}

void handleEvent(SDL_Event e) {
  if(!handleQuit(e)) {
    if(!handleMouse(e)) {
      if(!handleKeyboard(e)) {
        if(!handleJoycon(e)) {
          /* End of the line */
        }
      }
    }
  }
}

bool handleQuit(SDL_Event e) {
  if(e.type == SDL_QUIT) {
    shutdown = true;
    return true;
  } else {
    return false;
  }
}

bool handleMouse(SDL_Event e) {
  int x, y;
  if(e.type == SDL_MOUSEMOTION) {
    px = x; py = y;
    SDL_GetMouseState(&x, &y);
    if(ldown) {
      mouseI->mouseDrag(lx, ly, px, py, x, y);
    } else {
      mouseI->mouseMove(px, py, x, y);
    }
    return true;
  } else if(e.type == SDL_MOUSEBUTTONDOWN) {
    px = x; py = y;
    SDL_GetMouseState(&x, &y);
    if(e.button.button == SDL_BUTTON_LEFT) {
      lx = x; ly = y;
      ldown = true;
      mouseI->leftClickDown(x,y);
    } else if(e.button.button == SDL_BUTTON_RIGHT) {
      rdown = true;
      mouseI->rightClickDown(x,y);
    } else if(e.button.button == SDL_BUTTON_MIDDLE) {
      mdown = true;
      mouseI->middleClickDown(x,y);
    }
    return true;
  } else if(e.type == SDL_MOUSEBUTTONUP) {
    px = x; py = y;
    SDL_GetMouseState(&x, &y);
    if(e.button.button == SDL_BUTTON_LEFT) {
      ldown = false;
      mouseI->leftClickUp(x,y);
    } else if(e.button.button == SDL_BUTTON_RIGHT) {
      rdown = false;
      mouseI->rightClickUp(x,y);
    } else if(e.button.button == SDL_BUTTON_MIDDLE) {
      mdown = false;
      mouseI->middleClickUp(x,y);
    }
    return true;
  } else if(e.type == SDL_MOUSEWHEEL) {
    px = x; py = y;
    SDL_GetMouseState(&x, &y);
    if(e.wheel.y > 0) {
      mouseI->scrollUp(x,y);
    } else if(e.wheel.y < 0) {
      mouseI->scrollDown(x,y);
    }
    return true;
  } else {
    return false;
  }
}

bool handleKeyboard(SDL_Event e) {
  if(e.type == SDL_KEYDOWN) { 
    keyboardI->keyPress(e.key.keysym.sym);
    return true;
  } else if(e.type == SDL_KEYUP) {
    keyboardI->keyRelease(e.key.keysym.sym);
    return true;
  } else {
    return false;
  }
}

bool handleJoycon(SDL_Event e) {
  if(e.type == SDL_JOYAXISMOTION) {
    if(e.jaxis.axis == 0) {
      //joycons[e.jaxis.which]->moveLeftX(e.jaxis.value);
    } else if(e.jaxis.axis == 1) {
      //joycons[e.jaxis.which]->moveLeftY(e.jaxis.value);
    } else if(e.jaxis.axis == 3) {
      //joycons[e.jaxis.which]->moveRightX(e.jaxis.value);
    } else if(e.jaxis.axis == 4) {
      //joycons[e.jaxis.which]->moveRightY(e.jaxis.value);
    }
    return true;
  } else if(e.type == SDL_JOYBUTTONUP) {
    joyconI->buttonRelease(e.jbutton.button, e.jbutton.which);
    return true;
  } else if(e.type == SDL_JOYBUTTONDOWN) {
    joyconI->buttonPress(e.jbutton.button, e.jbutton.which);
    return true;
  } else {
    return false;
  }
}

void start_1thread_drawthread() {
  running = true;
  shutdown = false;
  initRenderthread();

  SDL_Event e;
  Uint32 eventsProcessed;
  st = SDL_GetTicks();

  // Initial Draw
  SDL_RenderClear(gRenderer);
  renderI->render(ut);
  et = SDL_GetTicks();
  if(et < MS_delay) SDL_Delay(MS_delay-et);
  SDL_Delay(MS_delay);
  SDL_RenderPresent(gRenderer);
  SDL_ShowWindow(gWindow);

  while(running) {
    ut = SDL_GetTicks() - st;
    st = ut + st;
    eventsProcessed = 0;
    while(SDL_PollEvent(&e) != 0 && eventsProcessed < maxEvents) {
      handleEvent(e);
      eventsProcessed++;
    }
    game->update(ut);
    SDL_LockMutex(renderLock);
    SDL_CondSignal(renderStart);
    SDL_UnlockMutex(renderLock);
    game->updateThreaded(ut);
    if(shutdown) running = false;
    SDL_CondWait(renderFinished, engineLock);
    et = SDL_GetTicks() - st;
    while(et < MS_delay && SDL_PollEvent(&e) != 0) {
      handleEvent(e);
      et = SDL_GetTicks() - st;
    }
    if(et < MS_delay) SDL_Delay(MS_delay-et);
    SDL_RenderPresent(gRenderer);
  }
  game->quit();
  SDL_UnlockMutex(engineLock);
}

