#ifndef MWINDOW_HEADER
#define MWINDOW_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/*********************************************************************
  MWindow: Contains the window and renderer. Responsible to clearing
  renderer and drawing to screen. VSYNC is disabled by default.
  Not responsible for FPS.
  To draw to screen, pass MWindow as argument, and draw directly to
  the renderer via getRenderer(). MWindow is very basic and only holds
  the window/renderer. It does not know how to add textures to the
  renderer.

  Author: Eric
 *********************************************************************/

class MWindow {

  public:
    MWindow();
    ~MWindow();
    void setVsync(bool);
    bool init(std::string, int, int, bool, bool);
    void show();
    void close();
    SDL_Renderer* getRenderer();
    void clear();
    void draw();
    int getWidth();
    int getHeight();
    void resizeRatio(int, int);
  private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    int width;
    int height;
    bool vsync;
    bool fullscreen;
    double ratio;

};

#endif

