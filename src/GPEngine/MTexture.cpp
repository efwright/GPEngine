#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "MRect.h"
#include "MFont.h"
#include "MColor.h"

#include "MTexture.h"
#include "MEngine.h"

using namespace GPE;

SDL_Surface*  loadSurface(std::string path) {
  SDL_Surface* loadedSurface = NULL;
  loadedSurface = IMG_Load(path.c_str());
  if(loadedSurface == NULL) {
    printf("Unable to load image %s! SDL_image Error: %s\n",
      path.c_str(), IMG_GetError());
  }
  SDL_Surface* temp =
    SDL_CreateRGBSurface(loadedSurface->flags, 
      loadedSurface->w, 
      loadedSurface->h,
      32,
      loadedSurface->format->Rmask, loadedSurface->format->Gmask,
      loadedSurface->format->Bmask, loadedSurface->format->Amask);
  if(temp == NULL) {
    printf("Unable to create image! SDL Error: %s\n",
      SDL_GetError());
  }
//printf("before blendnone\n");
  SDL_SetSurfaceBlendMode(temp, SDL_BLENDMODE_NONE);
//printf("after blendnone\n");
  if(SDL_BlitSurface(loadedSurface, NULL, temp, NULL) < 0) {
    printf("Unable to blit surface %s\n", SDL_GetError());
  }
  SDL_FreeSurface(loadedSurface);
  return temp;
}

SDL_Surface*  resizeSurface(SDL_Surface* src, int w, int h) {
  SDL_Surface* resizedSurface = 
    SDL_CreateRGBSurface(src->flags, w, h, 
      src->format->BitsPerPixel,
      src->format->Rmask, src->format->Gmask,
      src->format->Bmask, src->format->Amask);
  if(resizedSurface == NULL) {
    printf("Unable to create resized image! SDL Error: %s\n",
      SDL_GetError());
  }
//printf("Before blendresize\n");
  SDL_SetSurfaceBlendMode(resizedSurface, SDL_BLENDMODE_BLEND);
//printf("after blendresize\n");
  if(SDL_BlitScaled(src, NULL, resizedSurface, NULL) < 0) {
    printf("Error blitscaled %s\n", SDL_GetError());
  }
  return resizedSurface;
}

SDL_Texture*  createTexture(SDL_Surface* src)
{
  SDL_Texture* newTexture = NULL;
  newTexture =
    SDL_CreateTextureFromSurface(gRenderer, src);
  if(newTexture == NULL) {
    printf("Unable to create texture from surface! SDL Error: %s\n",
      SDL_GetError());
  }
//printf("Before blendcreatetexture\n");
  SDL_SetTextureBlendMode(newTexture, SDL_BLENDMODE_BLEND);
//printf("after blendcreatetexture\n");
  return newTexture;
}

SDL_Surface*  createSurface(SDL_Surface* src, int w, int h) {
  SDL_Surface* dst = NULL;
  dst = SDL_CreateRGBSurface(0, w, h,
    src->format->BitsPerPixel,
    src->format->Rmask, src->format->Gmask,
    src->format->Bmask, src->format->Amask);
  if(dst == NULL) {
    printf("Failed to create new surface: %s\n", SDL_GetError());
  }
//printf("Before blend\n");
  SDL_SetSurfaceBlendMode(dst, SDL_BLENDMODE_BLEND);
//printf("After blend\n");
  return dst;
}

std::string*  getPaths(int &size, std::string base,
                                std::string mod, std::string ext)
{
  std::string::size_type sz;
  int start = std::stoi(
    base.substr( base.length()-mod.length(), mod.length() ), &sz );
  int end = std::stoi( mod, &sz );
  if(start > end) {
    printf("Base and Mod values not compatible in MTexture::load\n");
    return NULL;
  }
  size = end-start+1;
  std::string* paths = new std::string[size];
  for(int i = start; i <= end; i++) {
    std::string pStr = std::to_string(i);
    for(int j = pStr.length(); j < mod.length(); j++) {
      pStr = "0" + pStr;
    }
    paths[i-start] = base.substr( 0, base.length()-mod.length() ) +
                     pStr + ext;
  }
  return paths;
}

SDL_Surface**  loadSurfaces(std::string* paths, int numPaths)
{
  SDL_Surface** surfaces = new SDL_Surface*[numPaths];
  for(int i = 0; i < numPaths; i++) {
    surfaces[i] = loadSurface(paths[i]);
  }
  return surfaces;
}

void  resizeSurfaces(SDL_Surface** surfaces, int numSurfaces,
                    int w, int h)
{
  for(int i = 0; i < numSurfaces; i++) {
    SDL_Surface* temp = resizeSurface(surfaces[i], w, h);
    SDL_FreeSurface(surfaces[i]);
    surfaces[i] = temp;
  }
}

SDL_Surface*  stitchSurfaces(SDL_Surface** surfaces,
  int numSurfaces, int x, int y)
{
  int w = surfaces[0]->w;
  int h = surfaces[0]->h;
  SDL_Surface* stitchedSurface = createSurface(surfaces[0],
    w*x, h*y);

  SDL_Rect srcRect = {0, 0, w, h};
  for(int i = 0; i < x; i++) {
    for(int j = 0; j < y; j++) {
      if(j*x+i >= numSurfaces) continue;
      SDL_Rect dstRect = {i*w, j*h, w, h};
      SDL_BlitSurface(surfaces[j*x+i], &srcRect,
                      stitchedSurface, &dstRect);
    }
  }
  return stitchedSurface;
}

GPE::MTexture::MTexture() {
  texture = NULL;
  width = 0;
  height = 0;
}

GPE::MTexture::~MTexture() {
  free();
}

void GPE::MTexture::free() {
  if(texture != NULL) {
    SDL_DestroyTexture(texture);
    texture = NULL;
  }
  width = 0;
  height = 0;
}

bool GPE::MTexture::load(std::string path) {
  free();
  SDL_Surface* loadedSurface = loadSurface(path);
  texture = createTexture(loadedSurface);

  width = loadedSurface->w;
  height = loadedSurface->h;

  SDL_FreeSurface(loadedSurface);
  return texture != NULL;
}

bool GPE::MTexture::load(std::string path,
 Uint8 r, Uint8 g, Uint8 b)
{
  free();
  SDL_Surface* loadedSurface = loadSurface(path);
  SDL_SetColorKey( loadedSurface, SDL_TRUE,
    SDL_MapRGB(loadedSurface->format, r, g, b) );
  texture = createTexture(loadedSurface);

  width = loadedSurface->w;
  height = loadedSurface->h;

  SDL_FreeSurface(loadedSurface);
  return texture != NULL;
}

bool GPE::MTexture::load(std::string base, std::string mod, std::string ext,
                    int x, int y)
{
  free();
  int numPaths = 0;
  std::string* paths = getPaths(numPaths, base, mod, ext);
  load(paths, numPaths, x, y);
  delete[] paths;
}

bool GPE::MTexture::load(std::string* paths, int numPaths,
                    int x, int y)
{
  free();
  if(numPaths <= 0) {
    printf("numPaths cannot be < 0 MTexture::load\n");
    return false;
  }

  SDL_Surface** surfaces = new SDL_Surface*[numPaths];
  for(int i = 0; i < numPaths; i++) {
    surfaces[i] = loadSurface(paths[i]);
  }

  int w = surfaces[0]->w;
  int h = surfaces[0]->h;
  SDL_Surface* stitchedSurface = createSurface(surfaces[0],
    w*x, h*y);

  SDL_Rect srcRect = {0, 0, w, h};
  for(int i = 0; i < x; i++) {
    for(int j = 0; j < y; j++) {
      if(j*x+i >= numPaths) continue;
      SDL_Rect dstRect = {i*w, j*h, w, h};
      SDL_BlitSurface(surfaces[j*x+i], &srcRect,
                      stitchedSurface, &dstRect);
    }
  }

  texture = createTexture(stitchedSurface);
  width = w*x;
  height = h*y;

  SDL_FreeSurface(stitchedSurface);
  for(int i = 0; i < numPaths; i++) {
    SDL_FreeSurface(surfaces[i]);
    surfaces[i] = NULL;
  }
  delete[] surfaces;
}

bool GPE::MTexture::loadScaled(std::string path,
                          int w, int h)
{
  free();

  SDL_Surface* loadedSurface = loadSurface(path);
  SDL_Surface* resizedSurface = resizeSurface(loadedSurface, w, h);
  texture = createTexture(resizedSurface);

  width = resizedSurface->w;
  height = resizedSurface->h;

  SDL_FreeSurface(loadedSurface);
  SDL_FreeSurface(resizedSurface);

  return texture != NULL;
}

bool GPE::MTexture::loadScaled(std::string path, int w)
{
  free();

  SDL_Surface* loadedSurface = loadSurface(path);
  double ratio = ((double) w) / ((double) loadedSurface->w);
  int h = (int) (((double) loadedSurface->h)*ratio);
  SDL_Surface* resizedSurface = resizeSurface(loadedSurface, w, h);

  texture = createTexture(resizedSurface);

  width = resizedSurface->w;
  height = resizedSurface->h;

  SDL_FreeSurface(loadedSurface);
  SDL_FreeSurface(resizedSurface);

  return texture != NULL;
}

bool GPE::MTexture::loadScaled(std::string path,
                          double percent)
{
  free();
  SDL_Surface* loadedSurface = loadSurface(path);
  SDL_Surface* resizedSurface = resizeSurface( loadedSurface,
    (int) (((double) loadedSurface->w)*percent),
    (int) (((double) loadedSurface->h)*percent) );
  texture = createTexture(resizedSurface);

  width = resizedSurface->w;
  height = resizedSurface->h;

  SDL_FreeSurface(loadedSurface);
  SDL_FreeSurface(resizedSurface);

  return texture != NULL;
}

bool GPE::MTexture::loadScaled(std::string path,
                          double percentWidth, double percentHeight)
{
  free();
  SDL_Surface* loadedSurface = loadSurface(path);
  SDL_Surface* resizedSurface = resizeSurface( loadedSurface,
    (int) (((double) loadedSurface->w)*percentWidth),
    (int) (((double) loadedSurface->h)*percentHeight) );
  texture = createTexture(resizedSurface);

  width = resizedSurface->w;
  height = resizedSurface->h;

  SDL_FreeSurface(loadedSurface);
  SDL_FreeSurface(resizedSurface);

  return texture != NULL;
}

bool GPE::MTexture::loadScaled(std::string base, std::string mod,
                          std::string ext,
                          int x, int y, int w, int h)
{
  free();
  int numPaths = 0;
  std::string* paths = getPaths(numPaths, base, mod, ext);
  loadScaled(paths, numPaths, x, y, w, h);
  delete[] paths;
}

bool GPE::MTexture::loadScaled(std::string base, std::string mod,
                          std::string ext,
                          int x, int y, int w)
{
  free();
  int numPaths = 0;
  std::string* paths = getPaths(numPaths, base, mod, ext);
  loadScaled(paths, numPaths, x, y, w);
  delete[] paths;
}

bool GPE::MTexture::loadScaled(std::string base, std::string mod,
                          std::string ext,
                          int x, int y, double percent)
{
  free();
  int numPaths = 0;
  std::string* paths = getPaths(numPaths, base, mod, ext);
  if(numPaths <= 0) {
    printf("numPaths cannot be < 0 MTexture::load\n");
    return false;
  }

  SDL_Surface** surfaces = loadSurfaces(paths, numPaths);
  int w = (int) (((double) surfaces[0]->w)*percent);
  int h = (int) (((double) surfaces[0]->h)*percent);
  resizeSurfaces(surfaces, numPaths, w, h);

  SDL_Surface* stitchedSurface = stitchSurfaces(surfaces,
    numPaths, x, y);

  texture = createTexture(stitchedSurface);
  width = w*x;
  height = h*y;

  SDL_FreeSurface(stitchedSurface);
  for(int i = 0; i < numPaths; i++) {
    SDL_FreeSurface(surfaces[i]);
    surfaces[i] = NULL;
  }
  delete[] surfaces;
  delete[] paths;
}

bool GPE::MTexture::loadScaled(std::string base, std::string mod,
                          std::string ext,
                          int x, int y,
                          double percentWidth, double percentHeight)
{
  free();
  int numPaths = 0;
  std::string* paths = getPaths(numPaths, base, mod, ext);
  if(numPaths <= 0) {
    printf("numPaths cannot be < 0 MTexture::load\n");
    return false;
  }

  SDL_Surface** surfaces = loadSurfaces(paths, numPaths);
  int w = (int) (((double) surfaces[0]->w)*percentWidth);
  int h = (int) (((double) surfaces[0]->h)*percentHeight);
  resizeSurfaces(surfaces, numPaths, w, h);

  SDL_Surface* stitchedSurface = stitchSurfaces(surfaces,
    numPaths, x, y);

  texture = createTexture(stitchedSurface);
  width = w*x;
  height = h*y;

  SDL_FreeSurface(stitchedSurface);
  for(int i = 0; i < numPaths; i++) {
    SDL_FreeSurface(surfaces[i]);
    surfaces[i] = NULL;
  }
  delete[] surfaces;
  delete[] paths;
}

bool GPE::MTexture::loadScaled(std::string* paths, int numPaths,
                          int x, int y, int w, int h)
{
  free();
  if(numPaths <= 0) {
    printf("numPaths cannot be < 0 MTexture::load\n");
    return false;
  }

  SDL_Surface** surfaces = loadSurfaces(paths, numPaths);
  resizeSurfaces(surfaces, numPaths, w, h);

  SDL_Surface* stitchedSurface = stitchSurfaces(surfaces,
    numPaths, x, y);

  texture = createTexture(stitchedSurface);
  width = w*x;
  height = h*y;

  SDL_FreeSurface(stitchedSurface);
  for(int i = 0; i < numPaths; i++) {
    SDL_FreeSurface(surfaces[i]);
    surfaces[i] = NULL;
  }
  delete[] surfaces;
}

bool GPE::MTexture::loadScaled(std::string* paths, int numPaths,
                          int x, int y, int w)
{
  free();
  if(numPaths <= 0) {
    printf("numPaths cannot be < 0 MTexture::load\n");
    return false;
  }

  SDL_Surface** surfaces = loadSurfaces(paths, numPaths);
  double ratio = ((double) w) / ((double) surfaces[0]->w);
  int h = (int) (((double) surfaces[0]->h)*ratio);
  resizeSurfaces(surfaces, numPaths, w, h);

  SDL_Surface* stitchedSurface = stitchSurfaces(surfaces,
    numPaths, x, y);

  texture = createTexture(stitchedSurface);
  width = w*x;
  height = h*y;

  SDL_FreeSurface(stitchedSurface);
  for(int i = 0; i < numPaths; i++) {
    SDL_FreeSurface(surfaces[i]);
    surfaces[i] = NULL;
  }
  delete[] surfaces;
}

bool GPE::MTexture::loadText(std::string text, MFont* font, MColor color)
{
  free();
  SDL_Surface* textSurface = TTF_RenderText_Solid(font->getTTFFont(),
    text.c_str(), {color.r, color.g, color.b});
  if(textSurface == NULL) {
    printf( "Unable to render text surface! SDL_ttf Error: %s\n",
      TTF_GetError() );
  } else {
    texture = createTexture(textSurface);
    width = textSurface->w;
    height = textSurface->h;
    SDL_FreeSurface(textSurface);
  }
  return texture != NULL;
}

int GPE::MTexture::getWidth() { return width; }

int GPE::MTexture::getHeight() { return height; }

MTexture * GPE::create_texture(std::string path) {
  MTexture *ntexture = new MTexture();
  if(ntexture->load(path)) {
    return ntexture;
  } else {
    delete ntexture;
    return NULL;
  }
}

MTexture * GPE::create_texture(std::string path, Uint8 r, Uint8 g, Uint8 b) {
  MTexture *ntexture = new MTexture();
  if(ntexture->load(path, r, g, b)) {
    return ntexture;
  } else {
    delete ntexture;
    return NULL;
  }
}

MTexture * GPE::create_texture(std::string path, std::string mod, std::string ext, int x, int y) {
  MTexture *ntexture = new MTexture();
  if(ntexture->load(path, mod, ext, x, y)) {
    return ntexture;
  } else {
    delete ntexture;
    return NULL;
  }
}

MTexture * GPE::create_texture(std::string *paths, int numPaths, int x, int y) {
  MTexture *ntexture = new MTexture();
  if(ntexture->load(paths, numPaths, x, y)) {
    return ntexture;
  } else {
    delete ntexture;
    return NULL;
  }
}

MTexture * GPE::create_texture_scaled(std::string path, int w, int h) {
  MTexture *ntexture = new MTexture();
  if(ntexture->loadScaled(path, w, h)) {
    return ntexture;
  } else {
    delete ntexture;
    return NULL;
  }
}

MTexture * GPE::create_texture_scaled(std::string path, int w) {
  MTexture *ntexture = new MTexture();
  if(ntexture->loadScaled(path, w)) {
    return ntexture;
  } else {
    delete ntexture;
    return NULL;
  }
}

MTexture * GPE::create_texture_scaled(std::string path, double percent) {
  MTexture *ntexture = new MTexture();
  if(ntexture->loadScaled(path, percent)) {
    return ntexture;
  } else {
    delete ntexture;
    return NULL;
  }
}

MTexture * GPE::create_texture_scaled(std::string path, double percentX, double percentY) {
  MTexture *ntexture = new MTexture();
  if(ntexture->loadScaled(path, percentX, percentY)) {
    return ntexture;
  } else {
    delete ntexture;
    return NULL;
  }
}

MTexture * GPE::create_texture_scaled(std::string base, std::string mod, std::string ext, int x, int y, int w, int h) {
  MTexture *ntexture = new MTexture();
  if(ntexture->loadScaled(base, mod, ext, x, y, w, h)) {
    return ntexture;
  } else {
    delete ntexture;
    return NULL;
  }
}

MTexture * GPE::create_texture_scaled(std::string base, std::string mod, std::string ext, int x, int y, int w) {
  MTexture *ntexture = new MTexture();
  if(ntexture->loadScaled(base, mod, ext, x, y, w)) {
    return ntexture;
  } else {
    delete ntexture;
    return NULL;
  }
}

MTexture * GPE::create_texture_scaled(std::string base, std::string mod, std::string ext, int x, int y, double percent) {
  MTexture *ntexture = new MTexture();
  if(ntexture->loadScaled(base, mod, ext, x, y, percent)) {
    return ntexture;
  } else {
    delete ntexture;
    return NULL;
  }
}

MTexture * GPE::create_texture_scaled(std::string base, std::string mod, std::string ext, int x, int y, double percentX, double percentY) {
  MTexture *ntexture = new MTexture();
  if(ntexture->loadScaled(base, mod, ext, x, y, percentX, percentY)) {
    return ntexture;
  } else {
    delete ntexture;
    return NULL;
  }
}

MTexture * GPE::create_texture_scaled(std::string *paths, int numPaths, int x, int y, int w, int h) {
  MTexture *ntexture = new MTexture();
  if(ntexture->loadScaled(paths, numPaths, x, y, w, h)) {
    return ntexture;
  } else {
    delete ntexture;
    return NULL;
  }
}

MTexture * GPE::create_texture_scaled(std::string *paths, int numPaths, int x, int y, int w) {
  MTexture *ntexture = new MTexture();
  if(ntexture->loadScaled(paths, numPaths, x, y, w)) {
    return ntexture;
  } else {
    delete ntexture;
    return NULL;
  }
}

MTexture * GPE::create_texture_text(std::string text, MFont* font, MColor color) {
  MTexture *ntexture = new MTexture();
  if(ntexture->loadText(text, font, color)) {
    return ntexture;
  } else {
    delete ntexture;
    return NULL;
  }
}

void  GPE::destroy_texture(MTexture* texture) {
  delete texture;
}

void GPE::MTexture::render(int x, int y){
  GPE::GPRect renderRect = {x,y,width,height};
  // Render the entire texture to renderRect
  SDL_RenderCopy(gRenderer, texture, NULL, &renderRect);
}

void GPE::MTexture::render(int x, int y, GPE::GPRect clip){
  GPE::GPRect renderRect = {x,y,clip.w,clip.h};
  // Render clip of texture to renderRect, width/height based on clip width/height
  SDL_RenderCopy(gRenderer, texture, &clip, &renderRect);
}
void GPE::MTexture::render(int x, int y, int anchorX, int anchorY){
  GPE::GPRect renderRect = {x-anchorX, y-anchorY, width, height};
  SDL_RenderCopy(gRenderer, texture, NULL, &renderRect);
}
void GPE::MTexture::render(int x, int y, GPE::GPRect clip, int anchorX, int anchorY){
  GPE::GPRect renderRect = {x-anchorX, y-anchorY, clip.w, clip.h};
  SDL_RenderCopy(gRenderer, texture, &clip, &renderRect);
}
void GPE::MTexture::renderCentered(int x, int y){
  render(x,y,width/2,height/2);
}
void GPE::MTexture::renderCentered(int x, int y, GPE::GPRect clip){
  render(x,y,clip,width/2,height/2);
}
void GPE::MTexture::renderBottomLeft(int x, int y){
  render(x,y,0,height);
}
void GPE::MTexture::renderBottomLeft(int x, int y, GPE::GPRect clip){
  render(x,y,clip,0,height);
}
void GPE::MTexture::renderBottomRight(int x, int y){
  render(x,y,width,height);
}
void GPE::MTexture::renderBottomRight(int x, int y, GPE::GPRect clip){
  render(x,y,clip,width,height);
}
void GPE::MTexture::renderTopRight(int x, int y){
  render(x,y,width,0);
}
void GPE::MTexture::renderTopRight(int x, int y, GPE::GPRect clip){
  render(x,y,clip,width,0);
}

void GPE::MTexture::renderResized(int x, int y, GPE::GPRect resize){
  GPE::GPRect renderRect = {x,y,resize.w,resize.h};
  // Render the entire texture to renderRect
  SDL_RenderCopy(gRenderer, texture, NULL, &renderRect);
}

void GPE::MTexture::renderResized(int x, int y, GPE::GPRect clip, GPE::GPRect resize){
  GPE::GPRect renderRect = {x,y,resize.w,resize.h};
  // Render clip of texture to renderRect, width/height based on clip width/height
  SDL_RenderCopy(gRenderer, texture, &clip, &renderRect);
}
void GPE::MTexture::renderResized(int x, int y, GPE::GPRect resize, int anchorX, int anchorY){
  GPE::GPRect renderRect = {x-anchorX, y-anchorY, resize.w, resize.h};
  SDL_RenderCopy(gRenderer, texture, NULL, &renderRect);
}
void GPE::MTexture::renderResized(int x, int y, GPE::GPRect clip, GPE::GPRect resize, int anchorX, int anchorY){
  GPE::GPRect renderRect = {x-anchorX, y-anchorY, resize.w, resize.h};
  SDL_RenderCopy(gRenderer, texture, &clip, &renderRect);
}
void GPE::MTexture::renderResizedCentered(int x, int y, GPE::GPRect resize){
  renderResized(x,y,resize,resize.w/2,resize.h/2);
}
void GPE::MTexture::renderResizedCentered(int x, int y, GPE::GPRect clip, GPE::GPRect resize){
  renderResized(x,y,clip,resize,resize.w/2,resize.h/2);
}
void GPE::MTexture::renderResizedBottomLeft(int x, int y, GPE::GPRect resize){
  renderResized(x,y,resize,0,resize.h);
}
void GPE::MTexture::renderResizedBottomLeft(int x, int y, GPE::GPRect clip, GPE::GPRect resize){
  renderResized(x,y,clip,resize,0,resize.h);
}
void GPE::MTexture::renderResizedBottomRight(int x, int y, GPE::GPRect resize){
  renderResized(x,y,resize,resize.w,resize.h);
}
void GPE::MTexture::renderResizedBottomRight(int x, int y, GPE::GPRect clip, GPE::GPRect resize){
  renderResized(x,y,clip,resize,resize.w,resize.h);
}
void GPE::MTexture::renderResizedTopRight(int x, int y, GPE::GPRect resize){
  renderResized(x,y,resize,resize.w,0);
}
void GPE::MTexture::renderResizedTopRight(int x, int y, GPE::GPRect clip, GPE::GPRect resize){
  renderResized(x,y,resize,clip,resize.w,0);
}

