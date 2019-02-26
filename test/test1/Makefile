CC=g++
EXE=test1
MAIN=test1

IDIR =../../include
ODIR = obj
LDIR =../../lib

CFLAGS=-I$(IDIR) -std=c++11

LIBS=-L$(LDIR) -lgpe -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net

_DEPS = GPEngine/GPEngine.h

DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = test1.o

OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

default: clean $(EXE)
	./$(EXE)

$(EXE): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

$(ODIR)/%.o: %.cpp $(DEPS) | mdir
	$(CC) -c -o $@ $< $(CFLAGS) $(LIBS)

mdir:
	mkdir -p $(ODIR)

.PHONY: clean

clean:
	-rm -rf $(ODIR) $(EXE)

