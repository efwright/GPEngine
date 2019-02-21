#ifndef MHITBOX_HEADER
#define MHITBOX_HEADER

#include <stdio.h>
#include <stdlib.h>

class MHitbox {
  public:
    int x, y, w, h;
    MHitbox()
      : x(0), y(0), w(0), h(0) { };
    MHitbox(int w_, int h_)
      : x(0), y(0), w(w_), h(h_) { };
    MHitbox(int x_, int y_, int w_, int h_)
      : x(x_), y(y_), w(w_), h(h_) { };
    void set(int x_, int y_) {
      x = x_; y = y_;
    }
};

class MHitcircle {
  public:
    int x, y, r;
    MHitcircle()
      : x(0), y(0), r(0) { };
    MHitcircle(int r_)
      : x(0), y(0), r(r_) { };
    MHitcircle(int x_, int y_, int r_)
      : x(x_), y(y_), r(r_) { };
    void set(int x_, int y_) {
      x = x_; y = y_;
    }
};

bool collision(MHitbox, MHitbox);
bool collision(MHitbox, MHitcircle);
bool collision(MHitcircle, MHitbox);
bool collision(MHitcircle, MHitcircle);

#endif

