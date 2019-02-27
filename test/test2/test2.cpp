#include <stdio.h>
#include <stdlib.h>
#include "GPEngine/GPEngine.h"

using namespace GPE;

GPE::MTexture *cat;

class Test2Game : public MGame {
  public:
  long timePassed;

  Test2Game() { timePassed = 0L; };

  void initRender(int x, int y, unsigned int f) override {
    printf("Game is initializing\n");
    cat = GPE::create_texture("cat.png");
  }

  void render(unsigned int ut) override {
    cat->render(GPE::screenWidth/2 - cat->getWidth()/2, GPE::screenHeight/2 - cat->getHeight()/2);
  }

  void update(long et) {
    timePassed += et;
    if(timePassed > 3000L) {
      printf("Stopping GPEngine\n");
      GPE::Engine_endGame();
    }
  }

  void quit() {
    printf("Game is quitting.\n");
    GPE::destroy_texture(cat);
  }

};

int main() {
  printf("Running test1...\n");

  printf("Initializing GPEngine\n");

  Test2Game *g = new Test2Game();

  GPE::Engine_Init("Test1", "", g, g, g, g, g);

  printf("Starting GPEngine\n");

  GPE::Engine_Start();

  printf("Finalizing GPEngine\n");

  GPE::Engine_Finalize();


  printf("Finished test1\n");
  return 0;
}
