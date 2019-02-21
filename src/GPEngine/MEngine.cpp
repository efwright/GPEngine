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

#include "MWindow.h"
#include "MTexture.h"
#include "MSpriteSheet.h"
#include "MRect.h"
#include "MSound.h"
#include "MJoycon.h"
#include "MMouseInterface.h"
#include "MJoyconInterface.h"
#include "MRenderInterface.h"
#include "MQueue.h"
#include "MUDPSocket.h"
#include "MPacket.h"

#include "MEngine.h"

SDL_cond* renderTrigger;
SDL_cond* doneRenderTrigger;
SDL_mutex* renderLock;
SDL_mutex* doneRenderLock;
MEngine* gEngine = NULL;
MWindow* gWindow = NULL;
SDL_Window* gSDLWindow = NULL;
SDL_Renderer* gSDLRenderer = NULL;
MMouse* gMouse = NULL;
int screenWidth = 0;
int screenHeight = 0;

/*********************************************************************
  C O N S T R U C T O R / D E S T R U C T O R
 *********************************************************************/
MEngine::MEngine() {
  //window = NULL;
  //mouse = NULL;
  joycons.clear();
  renderI = NULL;
  mouseI = NULL;
  keyboardI = NULL;
  joyconI = NULL;
  running = false;
  closeLock = 0;
  FPS = DEFAULT_FPS;
  FPMS = 1000/FPS;
  resX = DEFAULT_RESX;
  resY = DEFAULT_RESY;
  vsync = false;
  fullscreen = false;
  musicVolume = MAX_VOLUME;
  soundVolume = MAX_VOLUME;
  renderThread = NULL;
  gameSwitch = false;
  gameToSwitchTo = NULL;
}

MEngine::~MEngine() {

}

void MEngine::close() {
  gWindow->close();
  delete gWindow;
  delete gMouse;
  for(int i = 0; i < joycons.size(); i++) {
    if(joycons[i] != NULL) {
      delete joycons[i];
      joycons[i] = NULL;
    }
  }
  joycons.clear();
  renderI = NULL;
  mouseI = NULL;
  keyboardI = NULL;
  joyconI = NULL;
  Mix_Quit();
  IMG_Quit();
  SDL_Quit(); 
}


/*********************************************************************
  R E N D E R  T H R E A D
 *********************************************************************/
SDL_SpinLock gSDLTextureLock = 0;

int renderThreadFunc(void* data) {
  SDL_LockMutex(renderLock);
  do {
    SDL_CondWait(renderTrigger, renderLock);
    SDL_AtomicLock(&gSDLTextureLock);
    //gWindow->draw();
    gWindow->clear();
    gEngine->getRenderI()->render();
    SDL_AtomicUnlock(&gSDLTextureLock);

    /*if(gTextureQueue.size() > 0) {
      gTextureQueue.lock();
      MTexture* t = gTextureQueue.popLock();
      //t->createTexture();
      gTextureQueue.unlock();
    }*/

    SDL_LockMutex(doneRenderLock);
    SDL_CondSignal(doneRenderTrigger);
    SDL_UnlockMutex(doneRenderLock);
  } while(gEngine->isRunning());
  SDL_UnlockMutex(renderLock);
  return 0;
}

MQueue<MTexture*> gTextureQueue;

void clearTextureQueue() {
  gTextureQueue.lock();
  while(gTextureQueue.sizeLock() > 0) {
    MTexture* t = gTextureQueue.popLock();
    //t->createTexture();
  }
  gTextureQueue.unlock();
}

void clearTextureQueue(int num) {
  gTextureQueue.lock();
  int n = 0;
  while(n < num && gTextureQueue.sizeLock() > 0) {
    MTexture* t = gTextureQueue.popLock();
    //t->createTexture();
    n++;
  }
  gTextureQueue.unlock();
}


/*********************************************************************
  I N I T I A L I Z A T I O N
 *********************************************************************/
void MEngine::init(std::string name, std::string settings,
 MRenderInterface* ri, MMouseInterface* mi, MJoyconInterface* ji,
 MKeyboardInterface* ki, MGame* g) {
  gEngine = this;
  initSettings(settings);
  initWindow(name);
  initLowLevel();
  initSound();
  initInterfaces(ri, mi, ji, ki);
  initJoycons();
  initMouse();
  initGame(g);
  initRenderThread();
}

void MEngine::initWindow(std::string name) {
  if( SDL_Init( SDL_INIT_VIDEO | 
      SDL_INIT_JOYSTICK | 
      SDL_INIT_AUDIO ) < 0 ) { 
    printf( "SDL could not initialize! SDL_Error: %s\n",
      SDL_GetError() );
    exit(-1);
  }
  gWindow = new MWindow();
  if(!gWindow->init(name, resX, resY, vsync, fullscreen)) {
    exit(-1);
  }
}

void MEngine::initLowLevel() {
  if( !( IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG ) ) { 
    printf("SDL_image could not initialize! SDL_image Error: %s\n",
      IMG_GetError() ); 
    exit(-1);
  } 
  if(TTF_Init() == -1) {
    printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n",
      TTF_GetError() ); 
    exit(-1);
  }
  if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0 ) { 
    printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n",
      Mix_GetError()); 
    exit(-1);
  }
  if(SDLNet_Init() == -1) {
    printf("SDLNet_Init: %s\n", SDLNet_GetError());
    exit(-1);
  }
}

void MEngine::initInterfaces(MRenderInterface* ri,
 MMouseInterface* mi, MJoyconInterface* ji, MKeyboardInterface* ki) {
  joyconI = ji;
  mouseI = mi;
  renderI = ri;
  renderI->init();
  keyboardI = ki;
}

void MEngine::initJoycons() {
  int numJoycons = getNumJoysticks();
  joycons.resize(numJoycons);
  for(int i = 0; i < numJoycons; i++) {
    joycons[i] = new MJoycon();
    joycons[i]->init(this, i);
    joyconI->initJoycon(joycons[i]);
  }
}

void MEngine::initMouse() {
  gMouse = new MMouse();
  gMouse->init(this);
}

void MEngine::initSettings(std::string settings) {
  if(!loadSettings(settings)) {
    printf("Failed to load settings: %s\n", settings.c_str());
    loadDefaultSettings();
  }
}

void MEngine::initGame(MGame* g) {
  game = g;
  game->init(screenWidth, screenHeight);
}

void MEngine::initSound() {
  Mix_VolumeMusic(musicVolume);
  Mix_Volume(-1, soundVolume);
}

void MEngine::initRenderThread() {
  renderTrigger = SDL_CreateCond();
  renderLock = SDL_CreateMutex();
  doneRenderTrigger = SDL_CreateCond();
  doneRenderLock = SDL_CreateMutex();
  SDL_LockMutex(doneRenderLock);
  renderThread = SDL_CreateThread(renderThreadFunc,
   "RenderThread", NULL);
}


/*********************************************************************
  L O A D  S E T T I N G S
 *********************************************************************/
bool MEngine::loadSettings(std::string settings) {
  std::ifstream settingsFile;
  std::string line;
  settingsFile.open(settings, std::ios::in);
  if(settingsFile.is_open()) {
    while(std::getline(settingsFile, line)) {
      int equals = line.find_first_of("=", 0);
      if(equals <= 0) continue;
      std::string command = line.substr(0, equals);
      std::string val = line.substr(equals+1, line.length());
      if(command.compare("CRASH") == 0) { 
        std::string::size_type sz;
        int crash_report = std::stoi(val, &sz);
        if(crash_report != 0) {
          printf("Crash detected, loading default settings.\n");
          loadDefaultSettings();
          return true;
        }
      } else if(command.compare("FPS") == 0) {
        std::string::size_type sz;
        int FPS_num = std::stoi(val, &sz);
        if(FPS_num <= 0) {
          printf("FPS is set too low, loaded defaults\n");
          loadDefaultSettings();
          return true;
        } else {
          FPS = FPS_num;
          FPS = 1000/FPMS;
        }
      } else if(command.compare("RES") == 0) {
        int x = val.find_first_of("x", 0);
        if(x <= 0) {
          printf("Resolution incorrect format, loading defaults\n");
          loadDefaultSettings();
          return true;
        } else {
          std::string::size_type sz;
          int v1 = std::stoi(val.substr(0, x), &sz);
          int v2 = std::stoi(val.substr(x+1, val.length()), &sz);
          if(v1 < v2 || v1 < DEFAULT_RESX || v2 < DEFAULT_RESY) {
            printf("%i, %i is not a workable resolution\n", v1, v2);
            loadDefaultSettings();
            return true;
          } else {
            resX = v1; resY = v2;
          }
        } 
      } else if(command.compare("VSYNC") == 0) {
        std::string::size_type sz;
        int vs = std::stoi(val, &sz);
        if(vs == 0) {
          vsync = false;
        } else {
          vsync = true;
        }
      } else if(command.compare("MUSICVOLUME") == 0) {
        std::string::size_type sz;
        int s = std::stoi(val, &sz);
        if(s < MIN_VOLUME || s > MAX_VOLUME) {
          printf("Volume not possible, loading defaults.\n");
          loadDefaultSettings();
          return true;
        } else {
          musicVolume = s;
        }
      } else if(command.compare("SOUNDVOLUME") == 0) {
        std::string::size_type sz;
        int s = std::stoi(val, &sz);
        if(s < MIN_VOLUME || s > MAX_VOLUME) {
          printf("Volume not possible, loading defaults.\n");
          loadDefaultSettings();
          return true;
        } else {
          soundVolume = s;
        }
      } else if(command.compare("FULLSCREEN") == 0) {
        std::string::size_type sz;
        int fs = std::stoi(val, &sz);
        if(fs == 0) {
          fullscreen = false;
        } else {
          fullscreen = true;
        }
      }
    }
    return true;
  } else {
    printf("Failed to open %s\n", settings.c_str());
    return false;
  }
}

void MEngine::loadDefaultSettings() {
  FPS = DEFAULT_FPS;
  FPMS = 1000/FPS;
  resX = DEFAULT_RESX;
  resY = DEFAULT_RESY;
  vsync = false;
  fullscreen = false;
  musicVolume = MAX_VOLUME;
  soundVolume = MAX_VOLUME;
}


/*********************************************************************
  E V E N T  H A N D L E R S
 *********************************************************************/
void MEngine::handleEvent(SDL_Event e) {
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

bool MEngine::handleQuit(SDL_Event e) {
  if(e.type == SDL_QUIT) {
    stop();
    return true;
  } else {
    return false;
  }
}

bool MEngine::handleMouse(SDL_Event e) {
  int x, y;
  if(e.type == SDL_MOUSEMOTION) {
    SDL_GetMouseState(&x, &y);
    gMouse->move(x,y);
    return true;
  } else if(e.type == SDL_MOUSEBUTTONDOWN) {
    SDL_GetMouseState(&x, &y);
    if(e.button.button == SDL_BUTTON_LEFT) {
      gMouse->leftClickDown(x,y);
    } else if(e.button.button == SDL_BUTTON_RIGHT) {
      gMouse->rightClickDown(x,y);
    } else if(e.button.button == SDL_BUTTON_MIDDLE) {
      gMouse->middleClickDown(x,y);
    }
    return true;
  } else if(e.type == SDL_MOUSEBUTTONUP) {
    SDL_GetMouseState(&x, &y);
    if(e.button.button == SDL_BUTTON_LEFT) {
      gMouse->leftClickUp(x,y);
    } else if(e.button.button == SDL_BUTTON_RIGHT) {
      gMouse->rightClickUp(x,y);
    } else if(e.button.button == SDL_BUTTON_MIDDLE) {
      gMouse->middleClickUp(x,y);
    }
    return true;
  } else if(e.type == SDL_MOUSEWHEEL) {
    SDL_GetMouseState(&x, &y);
    if(e.wheel.y > 0) {
      gMouse->scrollUp(x,y);
    } else if(e.wheel.y < 0) {
      gMouse->scrollDown(x,y);
    }
    return true;
  } else {
    return false;
  }
}

bool MEngine::handleKeyboard(SDL_Event e) {
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

bool MEngine::handleJoycon(SDL_Event e) {
  if(e.type == SDL_JOYAXISMOTION) {
    if(e.jaxis.axis == 0) {
      joycons[e.jaxis.which]->moveLeftX(e.jaxis.value);
    } else if(e.jaxis.axis == 1) {
      joycons[e.jaxis.which]->moveLeftY(e.jaxis.value);
    } else if(e.jaxis.axis == 3) {
      joycons[e.jaxis.which]->moveRightX(e.jaxis.value);
    } else if(e.jaxis.axis == 4) {
      joycons[e.jaxis.which]->moveRightY(e.jaxis.value);
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


/*********************************************************************
  M A I N  L O O P
 *********************************************************************/
void MEngine::start() {
  SDL_AtomicLock(&closeLock);
  running = true;
  SDL_AtomicUnlock(&closeLock);
  
  gWindow->clear();
  renderI->render();
  gWindow->draw();
  gWindow->show();

  Uint32 ut, et;
  Uint32 st = SDL_GetTicks();
  SDL_Event e;
  while(running) {
    ut = SDL_GetTicks() - st;
    //printf("FPS=%zu\n", (Uint32) ((1.0*1000)/((double) ut)) );
    st = ut + st;
    while(SDL_PollEvent(&e) != 0) {
      handleEvent(e);
    }
    game->update(ut);
    SDL_LockMutex(renderLock);
    SDL_CondSignal(renderTrigger);
    SDL_UnlockMutex(renderLock);
    game->updateThreaded(ut);
    SDL_CondWait(doneRenderTrigger, doneRenderLock);
    contextSwitch();
    et = SDL_GetTicks() - st;
    while(et < FPMS && SDL_PollEvent(&e) != 0) {
      handleEvent(e);
      et = SDL_GetTicks() - st;
    }
    if(et < FPMS) {
      SDL_Delay(FPMS-et);
    }
    SDL_AtomicLock(&gSDLTextureLock);
    gWindow->draw();
    SDL_AtomicUnlock(&gSDLTextureLock);
  }
  SDL_UnlockMutex(doneRenderLock);
}

void MEngine::stop() {
  SDL_AtomicLock(&closeLock);
  running = false;
  SDL_AtomicUnlock(&closeLock);
}

void MEngine::contextSwitch() {
  if(gameSwitch) {
    gameSwitch = false;
    game = gameToSwitchTo;
    renderI = game;
    mouseI = game;
    keyboardI = game;
    joyconI = game;
    gameToSwitchTo = NULL;
  }
}

void MEngine::setGame(MGame* g) {
  gameToSwitchTo = g;
  gameSwitch = true;
}

