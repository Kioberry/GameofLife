#include <stdbool.h>
#include <SDL2/SDL.h>
#include "../include/gameData.h"
#include "../include/controlFunctions.h"

int main(int argc, char *args[])
{
    SDL_Event ev;
    // Start up SDL and create window
    if (!init())
    {
        printf("Failed to initialize!\n");
        return -1;
    }
    initchess(orgn);

    while (true)
    {
        while (SDL_PollEvent(&ev) != 0)
        {
            // check event type
            switch (ev.type)
            {
            case SDL_QUIT:
                // shut down
                break;
            }
        }

        if (!judgeNext())
        {
            printf("The state of the cells won't change anymore, the program will terminate.\n");
            break;
        }

        chess(ret);
        SDL_Delay(1000);
    }
    closeAll();
    return 0;
}
