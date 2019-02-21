#ifndef MTHREAD_HEADER
#define MTHREAD_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>

class MThread {
  public:
    MThread();
    ~MThread();
    typedef int (*ThreadFunc)(void*);
    ThreadFunc f;
    void* data;
    void start( int (*f)(void*), void* );
    void wait();
    void done();
    bool isRunning();
  private:
    bool running;
    SDL_Thread* tid;
  
};

#endif

