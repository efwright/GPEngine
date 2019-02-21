#ifndef MCOMMAND_HEADER
#define MCOMMAND_HEADER

#include <stdio.h>

//! MCommand has placeholder functions to be overridden

/*!
   MCommand is meant to be overriden. MCommand should be used for
   implementations of buttons, keys, swappable command objects, etc.

   MJoyconInterface implementations will most likely store
   customized MCommands for each button.
   MKeyboardInterface implementations will most likely store a
   customized MCommand for each hotbound key.

   Example of how to override:
    class MCommandOverride : public MCommand {
      void execute0() override;
      void execute1() override;
    };

    MCommand* command = new MCommandOverride();
    if(true) {
      command->execute0();
    } else {
      command->execute1();
    }
 */

class MCommand {
  public:
    virtual void execute0() {};
    virtual void execute1() {};
    virtual void execute2() {};
    virtual void execute3() {};
    virtual void execute4() {};
    virtual void execute5() {};
    virtual void execute6() {};
    virtual void execute7() {};
    virtual void execute8() {};
    virtual void execute9() {};
};

#endif
