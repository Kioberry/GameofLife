#include <stdio.h>
#include <SDL2/SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//初始化我们将要渲染的窗口
SDL_Window* gWindow = NULL;

//The surface contained by the window
//窗口包含的surface
SDL_Surface* gScreenSurface = NULL;

//我们将会载入并在屏幕上展示的图片
SDL_Surface* gHelloWorld = NULL;


//Starts up SDL and creates window
//函数功能：初始化SDL并创建窗口
int init();

//Loads media
//函数功能：加载多媒体文件
int loadMedia();

//Frees media and shuts down SDL
//函数功能：释放多媒体文件并关闭SDL
void closeall();