#ifndef _CONTROLFUN_H_
#define _CONTROLFUN_H_
//Starts up SDL and creates window
bool init();

//Frees media and shuts down SDL
void closeAll();

//Load the data from the file to initialise the world
int load(char filename[50]);

//Save the result of the current game
int save(char filename[50]);

void eventLoop();


#endif