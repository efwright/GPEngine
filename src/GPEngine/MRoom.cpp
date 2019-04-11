#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

#include "MRoom.h"
#include "Drawable.h"
#include "Updateable.h"

void GPE::MRoom::render(Uint32 et) {
  for(std::vector<GPE::Drawable*>::iterator it = drawObjects.begin();
      it != drawObjects.end();
      ++it)
    {
      (*it)->draw(et);
    }
}

void GPE::MRoom::update(Uint32 et) {
  for(std::vector<GPE::Updateable*>::iterator it = updateObjects.begin();
      it != updateObjects.end();
      ++it)
    {
      (*it)->update(et);
    }
}

