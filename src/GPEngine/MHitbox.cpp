#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>

#include "MHitbox.h"

bool collision(MHitbox a, MHitbox b) {
  return a.x < b.x + b.w &&
         a.x + a.w > b.x &&
         a.y < b.y + b.h &&
         a.y + a.h > b.y;
}

bool collision(MHitbox box, MHitcircle circle) {
  int dx = circle.x - std::max(box.x, std::min(circle.x, box.x + box.w));
  int dy = circle.y - std::max(box.y, std::min(circle.y, box.y + box.h));
  return dx*dx + dy*dy < circle.r*circle.r;
}

bool collision(MHitcircle circle, MHitbox box) {
  return collision(box, circle);
}

bool collision(MHitcircle a, MHitcircle b) {
  int dx = a.x - b.x;
  int dy = a.y - b.y;
  int dis = dx*dx + dy*dy;
  int rad = a.r+b.r;
  return dis < rad*rad;
}

