#ifndef GAME_FUN_H
#define GAME_FUN_H
extern int Maxrow, Maxcol;
extern int** orgn;
extern int** uorgn;
extern int** ret;

// Screen dimension constants
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const int BUTTON_AREA;

int dead(int row, int col);
int alive(int row, int col);
int load(char filename[50]);
int save(char filename[50]);
int Adjacent(int neighbor, int row, int col, int **board);
int initchess(int** orgn);
int chess(int** ret);
bool judgeNext(int **orgn, int **ret);
int MouseClick(int **uorgn, SDL_Point pos);
void loadIMG(SDL_Rect rect, const char *filename);
void drawOutline(int ver_x, int hor_y);

#endif