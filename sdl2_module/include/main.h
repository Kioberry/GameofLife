#include <stdio.h>
#include <SDL2/SDL.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void closeAll();

//Display the dead cells
int dead(int row, int col);

//Display the alive cells
int alive(int row, int col);

//Judge the next round of life
int judgeNext(int neighbor, int row, int col, int** board);

//Loads individual image as texture
SDL_Texture* loadTexture( char *path );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Current displayed texture
SDL_Texture* gTexture = NULL;

//Current displayed rectangle
SDL_Rect fillRect;

//Current displayed rectangle border
SDL_Rect outlineRect;

