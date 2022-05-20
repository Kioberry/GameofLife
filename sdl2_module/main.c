#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <malloc.h>
#include "controlFunctions.h"

/*problem: have to add a white image to be the background to prevent random error.*/
int main(int argc, char *args[])
{
    int count = 0;
    char filename1[50] = "state.txt";
    if (argc == 2)
    {
        count = atoi(args[1]);
        if (count <= 0)
        {
            printf("Invalid input of steps, the number cannot be string or integer that is smaller than 1 ");
            exit(0);
        }
        else
        {
            printf("OK, the program will last %d iterations\n", count);
            if (!init())
            {
                printf("Failed to initialize!\n");
                return -1;
            }
            eventLoop();
        }
    }
    if (argc == 1)
    {
        if (!init())
        {
            printf("Failed to initialize!\n");
            return -1;
        }
        eventLoop();
    }

    save(filename1);
    closeAll();

    return 0;
}
