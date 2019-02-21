#!/bin/bash

DIR="/home/efwright/GPEngine/"

unzip SDL2-2.0.9.zip
unzip SDL2_image-2.0.4.zip
unzip SDL2_mixer-2.0.4.zip
unzip SDL2_net-2.0.1.zip
unzip SDL2_ttf-2.0.15.zip

cd SDL2-2.0.9
mkdir build
cd build
../configure --prefix=$DIR
make -j4
make install

cd ../../SDL2_image-2.0.4
mkdir build
cd build
../configure --prefix=$DIR SDL_LIBS="-L$DIR/lib -lSDL2" SDL_CFLAGS="-I/$DIR/include/SDL2"
make -j4
make install

cd ../../SDL2_mixer-2.0.4
mkdir build
cd build
../configure --prefix=$DIR SDL_LIBS="-L$DIR/lib -lSDL2" SDL_CFLAGS="-I/$DIR/include/SDL2"
make -j4
make install

cd ../../SDL2_net-2.0.1
mkdir build
cd build
../configure --prefix=$DIR SDL_LIBS="-L$DIR/lib -lSDL2" SDL_CFLAGS="-I/$DIR/include/SDL2"
make -j4
make install

cd ../../SDL2_ttf-2.0.15
mkdir build
cd build
../configure --prefix=$DIR SDL_LIBS="-L$DIR/lib -lSDL2" SDL_CFLAGS="-I/$DIR/include/SDL2"
make -j4
make install

cd ../..

rm -rf SDL2-2.0.9
rm -rf SDL2_image-2.0.4
rm -rf SDL2_mixer-2.0.4
rm -rf SDL2_net-2.0.1
rm -rf SDL2_ttf-2.0.15

