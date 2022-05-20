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
void MouseClick(int** uorgn, int Mousex, int Mousey);
//Display the current state of the world
int chess();
int whetherClick();
void draw();

#endif