CC=g++
LIBNAME = gpe

DIR = GPEngine
IDIR =../../include
ODIR=../../build
LDIR =../../lib

NETWORKDIR=Network

CFLAGS=-I$(IDIR) -I$(IDIR)/$(DIR) -I$(IDIR)/$(DIR)/$(NETWORKDIR) -std=c++11 -O3

LIBS=-L$(LDIR) -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net -lm

_DEPS = MMouseInterface.h \
        MJoyconInterface.h \
        MRenderInterface.h \
        MKeyboardInterface.h \
        MGame.h \
        MRect.h \
        MSpriteSheet.h \
        MTexture.h \
        MJoycon.h \
        MSound.h \
        MMusic.h \
        MCommand.h \
        MAnimation.h \
        MThread.h \
        MFont.h \
        MColor.h \
        MEngine.h \
        MQueue.h \
        MHitbox.h \
        MRoom.h \
        Drawable.h \
        Updateable.h \
        $(NETWORKDIR)/MPacket.h \
        $(NETWORKDIR)/MUDPSocket.h \
        $(NETWORKDIR)/MTCPSocket.h \
        $(NETWORKDIR)/MTCPServer.h

DEPS = $(patsubst %,$(IDIR)/$(DIR)/%,$(_DEPS))

_OBJ = MSpriteSheet.o \
       MTexture.o \
       MJoycon.o \
       MSound.o \
       MMusic.o \
       MAnimation.o \
       MThread.o \
       MFont.o \
       MEngine.o \
       MHitbox.o \
       MRoom.o \
       $(NETWORKDIR)/MPacket.o \
       $(NETWORKDIR)/MUDPSocket.o \
       $(NETWORKDIR)/MTCPSocket.o \
       $(NETWORKDIR)/MTCPServer.o

OBJ = $(patsubst %,$(ODIR)/$(DIR)/%,$(_OBJ))


$(ODIR)/$(DIR)/%.o: %.cpp $(DEPS) | mdir
	$(CC) -c -o $@ $< $(CFLAGS) $(LIBS)

build: $(OBJ) | ldir
	ar rcs $(LDIR)/lib$(LIBNAME).a $^

mdir:
	mkdir -p $(ODIR)
	mkdir -p $(ODIR)/$(DIR)
	mkdir -p $(ODIR)/$(DIR)/$(NETWORKDIR)

ldir:
	mkdir -p $(LDIR)

.PHONY: clean

clean:
	rm -f $(ODIR)/$(DIR)/*.o $(ODIR)/$(DIR)/$(NETWORKDIR)/*.o *~ core

