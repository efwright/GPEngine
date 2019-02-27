#ifndef MANIMATION_HEADER
#define MANIMATION_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

#include "MSpriteSheet.h"

//! Interfaces with an MSpriteSheet to create animations.
/*!
 *  The MAnimation will cycle through the sprites to create an
 *  animation. The order of the sprites is by default 0->numSprites.
 *  You can also only use a subset of the total sprites. You may also 
 *  specify a subset of sprites to use, and which order to use them
 *  in. This may be useful for animating sprites that are on a very
 *  complex sprite sheet. To make the sprite change during runtime,
 *  you must call either update() or update(long). render(MWindow*,
 *  int, int) will render it to the screen.
 */

namespace GPE
{

class MAnimation;
MAnimation *create_animation(GPE::MSpriteSheet*, int);
MAnimation *create_animation(GPE::MSpriteSheet*, int, std::vector<int>);
MAnimation *create_animation(GPE::MSpriteSheet*, int, int, int);

class MAnimation {
  protected:
/*!
    The constuctor is currently not use for anything other than
    creating an instance of MAnimation. You can create a new instance
    with the constructor, and then initialize the instance with any of
    the init() member funcions.
*/
    MAnimation();

/*!
    The destructor will zero out some values, but ultimately does not
    destroy the spriteSheet. The spriteSheet should be destroyed on its
    own elsewhere in the code.
*/
    ~MAnimation();

//! Initialize the animation using all sprites
/*!
  \param newSpriteSheet is the MSpriteSheet to use. All sprites will be used.
  \param fps is how many frames of the animation should be cycled per second.
  \sa init(MSpriteSheet*, int, std::vector<int>)
  \sa init(MSpriteSheet*, int, int, int)
*/
    void init(GPE::MSpriteSheet* newSpriteSheet, int fps);

//! Initialize the animation with the specified sprite order
/*!
  \param newSpriteSheet is the MSpriteSheet to use. All sprites will be used.
  \param fps is how many frames of the animation should be cycled per second.
  \param useSpriteOrder is the order that the sprites should be used in.
  \sa init(MSpriteSheet*, int)
  \sa init(MSpriteSheet*, int, int, int)
*/
    void init(GPE::MSpriteSheet* newSpriteSheet, int fps, std::vector<int> useSpriteOrder);

//! Initialize the animation using subset of sprites
/*!
  \param newSpriteSheet is the MSpriteSheet to use. All sprites will be used.
  \param fps is how many frames of the animation should be cycled per second.
  \param start is the first sprite to use (inclusive)
  \param end is the last sprite to use (inclusive)
  \sa init(MSpriteSheet*, int)
  \sa init(MSpriteSheet*, int, std::vector<int>)
*/
    void init(GPE::MSpriteSheet* newSpriteSheet, int fps, int start, int end);

  public:

//! Render the current sprite at position x,y (using top left of sprite for anchor)
/*!
    \param window is the MWindow to render to
    \param x is the x coordinate of where to render the sprite
    \param y is the y coordinate of where to render the sprite
    \sa renderCentered(MWindow*, int, int)
*/
    void render( int x, int y);

//! Render the current sprite at position x,y (using center of sprite as anchor)
/*!
    \param window is the MWindow to render to
    \param x is the x coordinate of where to render the sprite (center of image
           will be at this point)
    \param y is the y coordinate of where to render the sprite (center of image
           will be at this point)
*/
    void renderCentered( int x, int y);

//! Render the current sprite at position x,y (using bottom right of sprite as anchor)
/*!
    \param window is the MWindow to render to
    \param x is the x coordinate of where to render the sprite (bottom right of image
           will be at this point)
    \param y is the y coordinate of where to render the sprite (bottom right of image
           will be at this point)
*/
    void renderBottomRight( int x, int y);

//! Update the animation to the next sprite
/*!
    \sa update(long)
*/
    void update();

//! Update the animation to the appropriate sprite based on FPS and elapsed time.
/*!
    \param elapsedTime is how much time to update by
    \sa update()
*/
    void update(long elapsedTime);

//! Update animation but do not repeat
    void updateNoRepeat(long elapsedTime);

//! Update animation with specified repeat
    void update(long et, bool repeat);

  protected:
//! Underlying spritesheet
    GPE::MSpriteSheet* spriteSheet;

//! The ordering that sprites appear in the animation
/*!
 *  With an MSimpleSpritesheet this will most likely be the order
 *  that the sprites appear (left to right, top to bottom).
 *  The more complex MSpriteSheet does not need to follow a natural
 *  order, and you may have times when you may have multiple
 *  MAnimations using different sprites from a single MSpriteSheet.
 */
    std::vector<int> spriteOrder;

//! Number of sprites in the animation
    int numSprites;

//! How many frames the animation should cycle through per second
    int FPS;

//! Number of miliseconds before the sprite should change, based on FPS
    long FPMS;

//! The sprite that will be drawn upon calling render()
    int currentSprite;

//! Current time elapsed, use to update currentSprite
    long currentTime;

  public:
    friend MAnimation *create_animation(GPE::MSpriteSheet*, int);
    friend MAnimation *create_animation(GPE::MSpriteSheet*, int,
      std::vector<int>);
    friend MAnimation *create_animation(GPE::MSpriteSheet*, int, int, int);

};

}

#endif

