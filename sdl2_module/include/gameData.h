#ifndef _GAME_DATA
#define _GAME_DATA_

float scale = 2.0;
int** orgn;
int** ret;
int Maxrow, Maxcol;

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// The window we'll be rendering to
SDL_Window *gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Current displayed texture
SDL_Texture* gTexture = NULL;

//Current displayed rectangle
SDL_Rect fillRect;

//Current displayed rectangle border
SDL_Rect outlineRect;

#endif