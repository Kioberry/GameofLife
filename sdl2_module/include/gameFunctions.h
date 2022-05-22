#ifndef _GAME_FUN_
#define _GAME_FUN_
void drawOutline(int ver_x, int hor_y);
int dead(int row, int col);
int alive(int row, int col);
int Adjacent(int neighbor, int row, int col, int **board);
//Judge the next round of life
bool judgeNext(int** orgn, int** ret);
//Display the initial state of the world
int initchess();
int whetherLast(SDL_Point pos, SDL_Rect rectup, SDL_Rect rectdown);
int MouseClick(int** uorgn, SDL_Point pos);
//Display the current state of the world
int chess();
int whetherClick();
void loadIMG(SDL_Rect rect, const char* filename);
void draw(bool ifSteps, int steps, int current);

#endif