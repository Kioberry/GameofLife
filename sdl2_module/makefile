vpath %.c src
SDL_LIB = -lSDL2 -lSDL2_image -Wl,-rpath=/usr/local/lib
SDL_INCLUDE = -I/usr/include
# generic build details

CC = gcc
CFLAGS = -Wall -c $(SDL_INCLUDE)
LDFLAGS = $(SDL_LIB)
EXE = rendering

OBJ = main.o
SRC= main.c

# compile to  object code


all: $(EXE)

# build executable

$(EXE): $(OBJ)
	$(CC) $< $(LDFLAGS) -o $@
	

# dependencies

$(OBJ):  $(SRC)
	$(CC) $(CFLAGS) $< -O $@

# clean up compilation

clean:
	rm -f $(OBJ) $(EXE)  

