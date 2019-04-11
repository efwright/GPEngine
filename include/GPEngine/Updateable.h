#ifndef MUPDATEABLE_HEADER
#define MUPDATEABLE_HEADER

namespace GPE {

class Updateable {
  public:
    virtual void update(Uint32) = 0;
  private:
};

}

#endif

