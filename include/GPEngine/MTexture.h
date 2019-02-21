#ifndef MTEXTURE_HEADER
#define MTEXTURE_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "MRect.h"
#include "MFont.h"
#include "MColor.h"

const SDL_RendererFlip MTEXTURE_NO_FLIP = SDL_FLIP_NONE;
const SDL_RendererFlip MTEXTURE_HORIZONTAL_FLIP = SDL_FLIP_HORIZONTAL;
const SDL_RendererFlip MTEXTURE_VERTICAL_FLIP = SDL_FLIP_VERTICAL;

//! Texture to be drawn to the screen.
/*!
 *  You can load images from a file and store them as an MTexture.
 *  You can also generate text using a font file. Loaded images can
 *  also be scaled by a percentage or to a specific size. The image
 *  can be rendererd to the screen, and can be rotated or flipped.
 *  The image can also be shrunk during rendering.
*/

class MTexture {
  public:
/*!
 *  The constructor is not currently used for anything other than
 *  creating an instance of MTexture. Then you should load either
 *  an image from a file, or generate text using a font.
*/
    MTexture();

//! The destructor will destroy the SDL_Texture
    ~MTexture();

//! Load an image from a file
/*!
 *  \param path the path of the file from current directory
 */
    bool load(std::string path);

//! Load an image from a file, make specified color transparent
/*!
 *  \param path the path of the file from current directory
 *  \param r red value to filter
 *  \param g green value to filter
 *  \param b blue value to filter
 */
    bool load(std::string path, 
              Uint8 r, Uint8 g, Uint8 b);

//! Load multiple images and stitch them together
/*!
 *  All images must be the same size, otherwise the drawing will
 *  have overlapping textures. If the number of images are not even,
 *  then the last few image spots will be blank white.
 *  \param base base string of file name (e.g. 0000)
 *  \param mod modify string to specify multiple images, for example
 *  use base = 0000 and mod = 2 to access images 0000, 0001, 0002
 *  \param ext image extension (jpg, png, etc)
 *  \param x number of images to stitch width-wise
 *  \param y number of images to stitch height-wise
 */
    bool load(std::string base, std::string mod, std::string ext,
               int x, int y);

//! Load multiple images and stitch them together
/*!
 *  All images must be the same size, otherwise the drawing will have
 *  overlapping textures. If the number of images are not even, then
 *  the last few spots will be blank white.
 *  \param paths the paths of all images to load
 *  \param numPaths how many paths there are
 *  \param x how many images width-wise
 *  \param y how many images height-wise
 */
    bool load(std::string* paths, int numPaths, 
              int x, int y);

//! Load an image and scale it to absolute size
/*!
 *  \param path the path of the file from current directory
 *  \param w the width to resize to
 *  \param h the height to resize to
 */
    bool loadScaled(std::string path,  int w, int h);

//! Load an image and scale width to absolute size, scale height to
//! maintain aspect ratio
/*!
 *  \param path the path of the file from current directory
 *  \param w the width to resize to
 *  \param h the height to resize to
 */
    bool loadScaled(std::string path,  int w);

//! Load an image and scale to percentage, maintain aspect ratio
/*!
 *  \param path the path of the file from current directory
 *  \param percent percentage to scale by (width and height)
 */
    bool loadScaled(std::string path,  double percent);

//! Load an image and scale to percentage, differing aspect ratio
/*!
 *  \param path the path of the file from current directory
 *  \param percentWidth percentage to scale width
 *  \param percentHeight percentage to scale height
 */
    bool loadScaled(std::string path, 
                    double percentWidth, double percentHeight);

//! Load multiple images, scale them to absolute size (individually)
//! and stitch them together
/*!
 *  All images will be resized to absolute size, so it does not
 *  matter what their initial size was. If the number of images are
 *  not even, then the last few image spots will be blank white.
 *  \param base base string of file name (e.g. 0000)
 *  \param mod modify string to specify multiple images, for example
 *  use base = 0000 and mod = 2 to access images 0000, 0001, 0002
 *  \param ext image extension (jpg, png, etc)
 *  \param x number of images to stitch width-wise
 *  \param y number of images to stitch height-wise
 *  \param w width to scale each sub-image to
 *  \param h height to scale each sub-image to
 */
    bool loadScaled(std::string base, std::string mod, std::string ext,
               int x, int y,
              int w, int h);

//! Load multiple images, scale width to absolute size (individually),
//! and scales height by raio and stitch them together
/*!
 *  All images will be resized to absolute size, so it does not
 *  matter what their initial size was. If the number of images are
 *  not even, then the last few image spots will be blank white.
 *  \param base base string of file name (e.g. 0000)
 *  \param mod modify string to specify multiple images, for example
 *  use base = 0000 and mod = 2 to access images 0000, 0001, 0002
 *  \param ext image extension (jpg, png, etc)
 *  \param x number of images to stitch width-wise
 *  \param y number of images to stitch height-wise
 *  \param w width to scale each sub-image to
 */
    bool loadScaled(std::string base, std::string mod, std::string ext,
               int x, int y, int w);

//! Load multiple images, scale them to by percent (maintain aspect
//! ratio), and stitch them together
/*!
 *  All images will be scaled down by percent. All images must be
 *  the same size, otherwise there will be image overlap. If the
 *  number of images are not even, then the last few image spots will
 *  be blank white.
 *  \param base base string of file name (e.g. 0000)
 *  \param mod modify string to specify multiple images, for example
 *  use base = 0000 and mod = 2 to access images 0000, 0001, 0002
 *  \param ext image extension (jpg, png, etc)
 *  \param x number of images to stitch width-wise
 *  \param y number of images to stitch height-wise
 *  \param percent percent to scale each sub-image by (maintaining
 *  aspect ratio
 */
    bool loadScaled(std::string base, std::string mod, std::string ext,
               int x, int y,
              double percent);

//! Load multiple images, scale them to by percent (aspect ratio may
//! not remain), and stitch them together
/*!
 *  All images will be scaled down by percent. All images must be
 *  the same size, otherwise there will be image overlap. If the
 *  number of images are not even, then the last few image spots will
 *  be blank white.
 *  \param base base string of file name (e.g. 0000)
 *  \param mod modify string to specify multiple images, for example
 *  use base = 0000 and mod = 2 to access images 0000, 0001, 0002
 *  \param ext image extension (jpg, png, etc)
 *  \param x number of images to stitch width-wise
 *  \param y number of images to stitch height-wise
 *  \param percentWidth percent to scale each sub-image width by
 *  \param percentHeight percent to scale each sub-image height by
 */
    bool loadScaled(std::string base, std::string mod, std::string ext,
               int x, int y,
              double percentWidth, double percentHeight);

//! Load multiple images, resize them to absolute size, and stitch
//! them together
/*!
 *  Images that are not the same size will be resized to absolute
 *  size. If the number of images are not even, then the last few
 *  spots will be blank white.
 *  \param paths the paths of all images to load
 *  \param numPaths how many paths there are
 *  \param x how many images width-wise
 *  \param y how many images height-wise
 *  \param w the width to resize images to
 *  \param h the height to resize images to
 */
    bool loadScaled(std::string* paths, int numPaths, 
              int x, int y, int w, int h);

//! Load multiple images, resize width to absolute size and height by
//! ratio, and stitch them together
/*!
 *  Images that are not the same size will be resized to absolute
 *  size. If the number of images are not even, then the last few
 *  spots will be blank white.
 *  \param paths the paths of all images to load
 *  \param numPaths how many paths there are
 *  \param x how many images width-wise
 *  \param y how many images height-wise
 *  \param w the width to resize images to
 */
    bool loadScaled(std::string* paths, int numPaths, 
              int x, int y, int w);

//! Convert string into text image using specified font
/*!
 *  \param text the words to render
 *  \param font the font to use (includes size)
 *  \param color the color of the text (r,g,b)
 */
    bool loadText(std::string text, MFont* font, MColor color);

//! Render texture to window, top left anchor
/*!
 *  \param x the x-coordinate to render to (top left default)
 *  \param y the y-coordinate to render to (top left default)
 *  \param clip not required, subimage of texture to render
 *  \param resize not required, rect width/height may be used
 *  to resize the image to absolute value
 */
    void render( int x, int y, MRect* clip = NULL,
                MRect* resize = NULL);

//! Render texture to window, user defined anchor
/*!
 *  \param x the x-coordinate to render to (top left default)
 *  \param y the y-coordinate to render to (top left default)
 *  \param clip not required, subimage of texture to render
 *  \param resize not required, rect width/height may be used
 *  to resize the image to absolute value
 *  \param anchorX x coord to anchor to
 *  \param anchorY y coord to anchor to
 */
    void render( int x, int y,
                int anchorX, int anchorY,
                MRect* clip = NULL, MRect* resize = NULL);

//! Render texture to window, using middle as anchor
/*!
 *  \param x the x-coordinate to render to (centered)
 *  \param y the y-coordinate to render to (centered)
 *  \param clip not required, subimage of texture to render
 *  \param resize not required, rect width/height may be used
 *  to resize the image to absolute value
 */
    void renderCentered( int x, int y,
                        MRect* clip = NULL,
                        MRect* resize = NULL);

//! Render texture to window, bottom left anchor
/*!
 *  \param x the x-coordinate to render to (bottom left)
 *  \param y the y-coordinate to render to (bottom left)
 *  \param clip not required, subimage of texture to render
 *  \param resize not required, rect width/height may be used
 *  to resize the image to absolute value
 */
    void renderBottomLeft( int x, int y,
                          MRect* clip = NULL,
                          MRect* resize = NULL);

//! Render texture to window, bottom right anchor
/*!
 *  \param x the x-coordinate to render to (bottom right)
 *  \param y the y-coordinate to render to (bottom right)
 *  \param clip not required, subimage of texture to render
 *  \param resize not required, rect width/height may be used
 *  to resize the image to absolute value
 */
    void renderBottomRight( int x, int y,
                          MRect* clip = NULL,
                          MRect* resize = NULL);

//! Render texture to window, top right anchor
/*!
 *  \param x the x-coordinate to render to (top right)
 *  \param y the y-coordinate to render to (top right)
 *  \param clip not required, subimage of texture to render
 *  \param resize not required, rect width/height may be used
 *  to resize the image to absolute value
 */
    void renderTopRight( int x, int y,
                          MRect* clip = NULL,
                          MRect* resize = NULL);

//! Render texture to window with specified anchor
/*!
 *  \param x the x-coordinate to render to
 *  \param y the y-coordinate to render to
 *  \param anchorX x point to anchor to (default top-left)
 *  \param anchorY y point to anchor to (default top-left)
 *  \param clip not required, subimage of texture to render
 *  \param resize not required, rect width/height may be used
 *  to resize the image to absolute value
 */
    void renderAnchored( int x, int y,
                          int anchorX, int anchorY,
                          MRect* clip = NULL,
                          MRect* resize = NULL);

//! Render texture with option of rotation and flip
/*!
 *  \param x the x-coordinate to render to
 *  \param y the y-coordinate to render to
 *  \param clip not required, subimage of texture to render
 *  \param resize not required, rect width/height may be used
 *  to resize the image to absolute value
 *  \param angle angle to rotate by, degrees, clockwise
 *  \param flip the direction to flip to, can be one of
 *  MTEXTURE_NO_FLIP, MTEXTURE_HORIZONTAL_FLIP, MTEXTURE_VERTICAL_FLIP
 */
    void renderEx( int x, int y,
                  double angle, SDL_RendererFlip flip,
                  MRect* clip = NULL,
                  MRect* resize = NULL);

//! Render texture with option of rotation and flip and centered
/*!
 *  \param x the x-coordinate to render to (centered)
 *  \param y the y-coordinate to render to (centered)
 *  \param clip not required, subimage of texture to render
 *  \param resize not required, rect width/height may be used
 *  to resize the image to absolute value
 *  \param angle angle to rotate by, degrees, clockwise
 *  \param flip the direction to flip to, can be one of
 *  MTEXTURE_NO_FLIP, MTEXTURE_HORIZONTAL_FLIP, MTEXTURE_VERTICAL_FLIP
 */
    void renderCenteredEx( int x, int y,
                  double angle, SDL_RendererFlip flip,
                  MRect* clip = NULL,
                  MRect* resize = NULL);
                  
//! Return width of texture
    int getWidth();

//! Return height of texture
    int getHeight();

  private:
    SDL_Texture* texture;
    int width;
    int height;

//! Destroy any existing loaded texture
    void free();

};

//! Load surface from path
SDL_Surface* loadSurface(std::string path);

//! Resize surface to absolute size
/*!
 *  Does not destroy source surface
 */
SDL_Surface* resizeSurface(SDL_Surface* src, int w, int h);

//! Create texture from surface
SDL_Texture* createTexture(SDL_Surface* src);

//! Create surface using metadata from src and of specified size
SDL_Surface* createSurface(SDL_Surface* src, int w, int h);

//! Convert base/mod/ext to the full path names
std::string* getPaths(int &size, std::string base,
                      std::string mod, std::string ext);

//! Load all surfaces from array of paths
SDL_Surface** loadSurfaces(std::string* paths, int numPaths);

//! Resize all surfaces from array of surfaces
/*!
 *  All old surfaces are destroyed and replace with the new
 *  resized ones
 */
void resizeSurfaces(SDL_Surface** surfaces, int numSurfaces,
                    int w, int h);

//! Stitch all surfaces together in array of surfaces
SDL_Surface* stitchSurfaces(SDL_Surface** surfaces, int numSurfaces,
                            int x, int y);

//////////////////////////////////////////////////////////////////////

MTexture *create_texture(std::string);
MTexture *create_texture(std::string, Uint8, Uint8, Uint8);
MTexture *create_texture(std::string, std::string, std::string, int, int);
MTexture *create_texture(std::string*, int, int, int);
MTexture *create_texture_scaled(std::string, int, int);
MTexture *create_texture_scaled(std::string, int);
MTexture *create_texture_scaled(std::string, double);
MTexture *create_texture_scaled(std::string, double, double);
MTexture *create_texture_scaled(std::string, std::string, std::string, int, int, int, int);
MTexture *create_texture_scaled(std::string, std::string, std::string, int, int, int);
MTexture *create_texture_scaled(std::string, std::string, std::string, int, int, double);
MTexture *create_texture_scaled(std::string, std::string, std::string, int, int, double, double);
MTexture *create_texture_scaled(std::string*, int, int, int, int, int);
MTexture *create_texture_scaled(std::string*, int, int, int, int);
MTexture *create_texture_text(std::string, MFont*, MColor);
void destroy_texture(MTexture*);

#endif

























