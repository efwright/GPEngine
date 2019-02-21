#include <stdio.h>
#include <stdlib.h>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>

#include "MThread.h"

int wrapper(void* d) {
  MThread* thread = (MThread*) d;
  (*thread->f)(thread->data);
  thread->done();
  return 0;
}

MThread::MThread() {
  running = false;
  tid = NULL;
}

MThread::~MThread() {
  running = false;
  tid = NULL;
}

void MThread::start( int (*func)(void*), void* d ) {
  if(running) {
    printf("Thread is already running.\n");
    exit(-1);
  }
  running = true;
  f = func;
  data = d;
  tid = SDL_CreateThread(wrapper, "", (void*) this );
  if(tid == NULL) {
    printf("Could not initialize SDL thread: %s\n",
     SDL_GetError());
  }
}

void MThread::wait() {
  SDL_WaitThread(tid, NULL);
}

void MThread::done() {
  running = false;
}

bool MThread::isRunning() {
  return running;
}
