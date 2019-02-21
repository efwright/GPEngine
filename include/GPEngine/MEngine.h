#ifndef MENGINE_HEADER
#define MENGINE_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include "MWindow.h"
#include "MJoycon.h"
#include "MMouse.h"
#include "MGame.h"
#include "MJoycon.h"
#include "MMouseInterface.h"
#include "MJoyconInterface.h"
#include "MRenderInterface.h"
#include "MKeyboardInterface.h"
#include "MQueue.h"
#include "MTexture.h"

class MMouse;
class MJoycon;
class Mjoycon;
class MGame;
class MJoyconInterface;
class MKeyboardInterface;
class MMouseInterface;
class MKeyboardInterface;

/*********************************************************************
  MEngine:
   MEngine is in charge of handling most of the underlying engine.
   It will be the direct line of communication for all lines of
   I/O (mouse, keyboard, game controller, video, and audio). To
   communicate with the engine, you will need to use a corresponding
   interface (for example: MKeyboardInterface). The engine will
   feed the input information directly from the I/O device.

   There should only ever be one MEngine, and MEngine will contain
   and manage the MWindow, MMouse, MJoycons, and the main loop.

  Notes:
   Allow user to choose display, may be useful for finding correct
   refresh rate for vsync. Will need to know:
    SDL_DisplayMode current;
    SDL_Init(SDL_INIT_VIDEO);
    for(i = 0; i < SDL_GetNumVideoDisplays(); ++i){
      if(SDL_GetCurrentDisplayMode(i, &current) < 0) {
        printf("Could not get display mode for video display #%d: %s",
         i, SDL_GetError());
      } else {
        printf("Display #%d: current display mode is %dx%dpx @ %dhz.",
         i, current.w, current.h, current.refresh_rate);
      }
    }

  Author: Eric
 *********************************************************************/

// C L A S S  M E N G I N E ///////////////////////////////////////////
class MEngine {
  public:
    MEngine();
    ~MEngine();
    void close();


// E N G I N E  A T T R I B U T E S ///////////////////////////////////
  private:
    //MWindow* window;
    //MMouse* mouse;
    std::vector<MJoycon*> joycons;


// I N T E R F A C E S ////////////////////////////////////////////////
  private:
    MRenderInterface*   renderI;
    MMouseInterface*    mouseI;
    MKeyboardInterface* keyboardI;
    MJoyconInterface*   joyconI;
    MGame*              game;


// G A M E  S W I T C H ///////////////////////////////////////////////
  private:
    bool gameSwitch;
    MGame* gameToSwitchTo;
    void contextSwitch();
  public:
    void setGame(MGame* g);


// I N I T I A L I Z A T I O N ////////////////////////////////////////
  public:
    void init(std::string, std::string, MRenderInterface*,
     MMouseInterface*, MJoyconInterface*, MKeyboardInterface*,
     MGame*);
  private:
    void initWindow(std::string);
    void initLowLevel();
    void initInterfaces(MRenderInterface*, MMouseInterface*,
     MJoyconInterface*, MKeyboardInterface*);
    void initJoycons();
    void initMouse();
    void initSettings(std::string);
    void initGame(MGame*);
    void initSound();
    void initRenderThread();


// E V E N T  H A N D L E R S /////////////////////////////////////////
  private:
    void handleEvent(SDL_Event);
    bool handleQuit(SDL_Event);
    bool handleMouse(SDL_Event);
    bool handleKeyboard(SDL_Event);
    bool handleJoycon(SDL_Event);


// M A I N  L O O P ///////////////////////////////////////////////////
  public:
    void start();
    void stop();
  private:
    bool running;
    SDL_SpinLock closeLock;
    SDL_Thread* renderThread;


// S E T T I N G S ////////////////////////////////////////////////////
  public:
    bool loadSettings(std::string);
    void loadDefaultSettings();
  private:
    Uint32 FPS;
    Uint32 FPMS;
    int resX, resY;
    bool vsync;
    bool fullscreen;
    int musicVolume; // 0->128
    int soundVolume; // 0->128
    const int MIN_VOLUME = 0;
    const int MAX_VOLUME = 128;
    const int DEFAULT_RESX = 640;
    const int DEFAULT_RESY = 480;
    const int DEFAULT_FPS = 60; 


// G E T T E R S //////////////////////////////////////////////////////
  public:
    //MWindow* getWindow() { return window; }
    //MMouse* getMouse() { return mouse; }
    MJoycon* getJoycon(int j) { return joycons[j]; }
    std::vector<MJoycon*> getJoycons() { return joycons; }
    MRenderInterface* getRenderI() { return renderI; }
    MMouseInterface* getMouseI() { return mouseI; }
    MKeyboardInterface* getKeyboardI() { return keyboardI; }
    MJoyconInterface* getJoyconI() { return joyconI; }   
    MGame* getGame() { return game; } 
    bool isRunning() { return running; }
};

// G L O B A L S //////////////////////////////////////////////////////

extern MEngine* gEngine;
extern MWindow* gWindow;
extern SDL_Window* gSDLWindow;
extern SDL_Renderer* gSDLRenderer;
extern int screenWidth;
extern int screenHeight;
extern MMouse* gMouse;
extern SDL_SpinLock gSDLTextureLock;


// R E N D E R E R ////////////////////////////////////////////////////
extern MQueue<MTexture*> gTextureQueue;
void clearTextureQueue();
void clearTextureQueue(int);

#endif

