#include <stdio.h>
#include <stdlib.h>
#include "GPEngine/GPEngine.h"

class Test1Game : public MGame {
  public:
  long timePassed;

  Test1Game() { timePassed = 0L; };

  void update(Uint32 et) {
    timePassed += et;
    if(timePassed > 1000L) {
      printf("Stopping GPEngine\n");
      GPE::Engine_endGame();
    }
  }

  void quit() {
    printf("Game is quitting.\n");
  }

};

int main() {
  printf("Running test1...\n");

  printf("Initializing GPEngine\n");

  Test1Game *g = new Test1Game();

  GPE::Engine_Init("Test1", "", g, g, g, g, g);

  printf("Starting GPEngine\n");

  GPE::Engine_Start();

  printf("Finalizing GPEngine\n");

  GPE::Engine_Finalize();


  printf("Finished test1\n");
  return 0;
}
