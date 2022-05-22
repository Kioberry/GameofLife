
# code details
vpath %.h include
vpath %.c src
EXE_DIR = .
EXE = $(EXE_DIR)/rendering

SRC= main.c game.c

# generic build details

CC =     gcc
CFLAGS = -Wall -O
LIBS =   -lSDL2 -lSDL2_image

# compile to  object code

OBJ= $(SRC:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $< 

# build executable

$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $(EXE) $(LIBS)

# clean up compilation

clean:
	rm -f *.txt $(OBJ) $(EXE)

# dependencies

main.o:  main.c controlFunctions.h
game.o:  game.c gameData.h gameFunctions.h



