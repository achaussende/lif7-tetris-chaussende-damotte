CC=gcc
CFLAGS=-Wall -ggdb -pedantic
EXEC_NAME= ./bin/jeu
LIBS= -L./lib/FMOD/lib/ -lSDL -lSDL_ttf -lm -lfmodex

OBJDIR=obj
SRCDIR=src

OBJ_FILES= $(OBJDIR)/main.o $(OBJDIR)/LoopTETRIS_SDL.o $(OBJDIR)/tetris.o $(OBJDIR)/board.o $(OBJDIR)/player.o $(OBJDIR)/piece.o $(OBJDIR)/binarytrees.o 

all: $(EXEC_NAME)

$(EXEC_NAME): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $(EXEC_NAME)  $(LIBS)
	
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<
	
clean:
	rm $(OBJ_FILES)
