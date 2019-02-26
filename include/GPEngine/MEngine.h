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

#include "MGame.h"
#include "MMouseInterface.h"
#include "MJoyconInterface.h"
#include "MRenderInterface.h"
#include "MKeyboardInterface.h"

class MGame;
class MJoyconInterface;
class MKeyboardInterface;
class MMouseInterface;
class MKeyboardInterface;

namespace GPE
{

  extern SDL_Window* gWindow;
  extern SDL_Renderer* gRenderer;

  extern int screenWidth;
  extern int screenHeight;
  extern Uint32 FPS;
  extern Uint32 MS_delay;
  extern int musicVolume;
  extern int soundVolume;

  void Engine_Init(std::string, std::string,
   MRenderInterface*, MMouseInterface*, MJoyconInterface*,
   MKeyboardInterface*, MGame*);
  void Engine_Finalize();
  void Engine_Start();
  void Engine_swapMouse(MMouseInterface* mi);
  void Engine_swapKeyboard(MKeyboardInterface* ki);
  void Engine_swapJoycon(MJoyconInterface* ji);
  void Engine_swapRenderer(MRenderInterface* ri);
  void Engine_swapGame(MGame* g);
  void Engine_endGame();
  void Engine_pause();
  void Engine_pauseUpdate();
  void Engine_pauseDraw();
  void Engine_unpause();
  void Engine_unpauseUpdate();
  void Engine_unpauseDraw();

}

#endif

