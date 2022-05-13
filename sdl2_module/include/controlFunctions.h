#ifndef _CONTROL_FUN
#define _CONTROL_FUN
//Starts up SDL and creates window
bool init();

//Frees media and shuts down SDL
void closeAll();

//Judge the next round of life
bool judgeNext();

//Display the initial state of the world
int initchess(int** board);

//Display the current state of the world
int chess(int** board);


#endif