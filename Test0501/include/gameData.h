#ifndef _GAME_DATA_H
#define _GAME_DATA_H
#define FRAMERATE 2
#define START_FILE_NAME "images/Game2.png"
#define CLICK_FILE_NAME "images/Title.png"
#define OVER_FILE_NAME "images/OVER.png"
#define UP_FILE_NAME "images/up.png"
#define DOWN_FILE_NAME "images/down.png"
#define ITER_FILE_NAME "images/iter.png"

enum GameState
{
    START,
    LASTB,
    LASTA,
    MODE,
    FIRST,
    UFIRST,
    PLAYING,
    UPLAYING,
    OVER
}gameState;

// The window we'll be rendering to
SDL_Window *gWindow = NULL;

// The window renderer
SDL_Renderer *gRenderer = NULL;

// Current displayed texture
SDL_Texture *gTexture = NULL;

// Current displayed rectangle
SDL_Rect fillRect;

SDL_Point pos;
SDL_Point pos1;
#endif