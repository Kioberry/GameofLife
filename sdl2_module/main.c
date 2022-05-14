#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <malloc.h>
#include "controlFunctions.h"

/*problem: have to add a white image to be the background to prevent random error.*/
int main(int argc, char *args[])
{
    int count = 0;
    bool quit = false;
    SDL_Event event;
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
            initchess();
            SDL_Delay(3000);

            int i = 0;
            while (i < 3)
            {
                if (!judgeNext())
                {
                    printf("The state of the cells won't change anymore, the program will terminate.\n");
                    SDL_Delay(1500);
                    break;
                }
                chess();
                SDL_Delay(3000);
                i++;
            }
        }
    }
    if (argc == 1)
    {
        printf("The program will keep evolving until it is terminate\n");
        if (!init())
        {
            printf("Failed to initialize!\n");
            return -1;
        }
        initchess();
        SDL_Delay(2000);

        while (true)
        {
            if (!judgeNext())
            {
                printf("The state of the cells won't change anymore, the program will terminate.\n");
                SDL_Delay(1500);
                break;
            }
            chess();
            SDL_Delay(2000);
        }
    }

    while (!quit)
    {
        SDL_WaitEvent(&event);

        switch (event.type)
        {
        case SDL_QUIT:
            quit = true;
            break;
        }
    }
    save(filename1);
    closeAll();

    return 0;
}
