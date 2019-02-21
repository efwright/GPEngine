#ifndef MQUEUE_HEADER
#define MQUEUE_HEADER

#include <stdio.h>
#include <queue>
#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>

template <class T>
class MQueue {
  private:
    std::queue<T> queue;
    SDL_SpinLock qlock;
  public:
    MQueue() {
      qlock = 0;
    }

    ~MQueue() { }

    void lock() {
      SDL_AtomicLock(&qlock);
    }

    void unlock() {
      SDL_AtomicUnlock(&qlock);
    }

    T popLock() {
      T ele = queue.front();
      queue.pop();
      return ele;
    }

    int sizeLock() {
      return queue.size();
    }

    void push(T ele) {
      SDL_AtomicLock(&qlock);
      queue.push(ele);
      SDL_AtomicUnlock(&qlock);
    }

    T top() {
      SDL_AtomicLock(&qlock);
      T ele = queue.front();
      SDL_AtomicUnlock(&qlock);
      return ele;
    }

    T pop() {
      SDL_AtomicLock(&qlock);
      T ele = queue.front();
      queue.pop();
      SDL_AtomicUnlock(&qlock);
      return ele;
    }

    int size() {
      SDL_AtomicLock(&qlock);
      int s = queue.size();
      SDL_AtomicUnlock(&qlock);
      return s;
    }
};

#endif

