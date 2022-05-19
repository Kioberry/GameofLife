#ifndef _GAME_DATA_
#define _GAME_DATA_
#define FRAMERATE 3



int Maxrow, Maxcol;

int** orgn;
int** ret;

enum GameState
{
    START,
    FIRST,
    PLAYING,
    OVER
}gameState;


// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int BUTTON_AREA = 80;


// The window we'll be rendering to
SDL_Window *gWindow = NULL;

// The window renderer
SDL_Renderer *gRenderer = NULL;

// Current displayed texture
SDL_Texture *gTexture = NULL;

// Current displayed rectangle
SDL_Rect fillRect;

#endif