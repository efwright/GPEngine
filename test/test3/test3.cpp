#include <stdio.h>
#include <stdlib.h>
#include "GPEngine/GPEngine.h"

using namespace GPE;

class Test3Game : public MGame {
  public:
  long timePassed;
  GPE::MTexture* loading;
  GPE::MSpriteSheet* loadingS;
  GPE::MAnimation* loadingA;

  Test3Game() { timePassed = 0L; };

  void initRender(int x, int y, unsigned int f) override {
    printf("Game is initializing\n");
    loading = GPE::create_texture("images/load-00", "47", ".png",
      5, 10);
    loadingS = GPE::create_spritesheet(loading, 5, 10, 48);
    loadingA = GPE::create_animation(loadingS, 30);
  }

  void render(unsigned int ut) override {
    loadingA->render(0,0);
  }

  void update(long et) {
    timePassed += et;
    if(timePassed > 3000L) {
      printf("Stopping GPEngine\n");
      GPE::Engine_endGame();
    }
    loadingA->update(et);
  }

  void quit() {
    printf("Game is quitting.\n");
  }

};

int main() {
  printf("Running test1...\n");

  printf("Initializing GPEngine\n");

  Test3Game *g = new Test3Game();

  GPE::Engine_Init("Test3", "", g, g, g, g, g);

  printf("Starting GPEngine\n");

  GPE::Engine_Start();

  printf("Finalizing GPEngine\n");

  GPE::Engine_Finalize();


  printf("Finished test3\n");
  return 0;
}
