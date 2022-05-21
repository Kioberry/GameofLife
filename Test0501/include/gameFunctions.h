#ifndef GAME_FUN_H
#define GAME_FUN_H

extern int Maxrow, Maxcol;
extern int** orgn;
extern int** uorgn;
extern int** ret;
int dead(int row, int col);
int alive(int row, int col);
int load(char filename[50]);
int save(char filename[50], int** board);
int initchess(int** orgn);
int chess(int** ret);

int testsave(char filename[50]);

#endif