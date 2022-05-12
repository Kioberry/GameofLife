// Example program:
// Using SDL2 to create an application window

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <malloc.h>
#include "string.h"
#include "stdbool.h"
#include "../include/main.h"

float scale = 2.0;
int Maxrow, Maxcol;
int isFlag = 0;

bool init()
{
	// Initialization flag
	bool success = true;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		// Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		// Create window
		gWindow = SDL_CreateWindow("Chess", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			// Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				// Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);

				// Initialize PNG loading
				//  int imgFlags = IMG_INIT_PNG;
				//  if( !( IMG_Init( imgFlags ) & imgFlags ) )
				//  {
				//  	printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
				//  	success = false;
				//  }
			}
		}
	}

	return success;
}

bool loadMedia()
{
	// Loading success flag
	bool success = true;

	// Load PNG texture
	gTexture = loadTexture("texture.png");
	if (gTexture == NULL)
	{
		printf("Failed to load texture image!\n");
		success = false;
	}

	return success;
}

void closeAll()
{
	// Free loaded image
	SDL_DestroyTexture(gTexture);
	gTexture = NULL;

	// Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	// Quit SDL subsystems
	IMG_Quit();
	atexit(SDL_Quit);
}

SDL_Texture *loadTexture(char *path)
{
	// The final texture
	SDL_Texture *newTexture = NULL;

	// Load image at specified path
	SDL_Surface *loadedSurface = IMG_Load(path);
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
	}
	else
	{
		// Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
		}

		// Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}

int dead(int row, int col)
{
	if (row >= 0 && row < Maxrow && col >= 0 && col < Maxcol)
	{
		fillRect.x = 100 + row * 17;
		fillRect.y = 100 + col * 17;
		fillRect.w = 16;
		fillRect.h = 16;
		//渲染红色填充四边形
		SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
		SDL_RenderFillRect(gRenderer, &fillRect);
		outlineRect.x = 99 + row * 17;
		outlineRect.y = 99 + col * 17;
		outlineRect.w = 17;
		outlineRect.h = 17;
		//渲染grey轮廓的四边形
		SDL_RenderSetScale(gRenderer, scale, scale);
		SDL_SetRenderDrawColor(gRenderer, 209, 206, 220, 0);
		SDL_RenderDrawRect(gRenderer, &outlineRect);
		return 0;
	}
	else
	{
		return -1;
	}
}

int alive(int row, int col)
{
	if (row >= 0 && row < Maxrow && col >= 0 && col < Maxcol)
	{
		fillRect.x = 100 + row * 17;
		fillRect.y = 100 + col * 17;
		fillRect.w = 16;
		fillRect.h = 16;
		//渲染红色填充四边形
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
		SDL_RenderFillRect(gRenderer, &fillRect);
		outlineRect.x = 99 + row * 17;
		outlineRect.y = 99 + col * 17;
		outlineRect.w = 17;
		outlineRect.h = 17;
		//渲染grey轮廓的四边形
		SDL_RenderSetScale(gRenderer, scale, scale);
		SDL_SetRenderDrawColor(gRenderer, 209, 206, 220, 0);
		SDL_RenderDrawRect(gRenderer, &outlineRect);
		return 0;
	}
	else
	{
		return -1;
	}
}

int initchess(int **board)
{
	int i, j, row, col;
	int count = 0;
	for (row = 0; row != Maxrow; row++)
	{
		for (col = 0; col != Maxcol; col++)
		{
			if (board[row][col] != 1 && board[row][col] != 0)
			{
				printf("The original-state array hasn't been initialized.\n");
				return -1;
			}
		}
	}
	for (i = 0; i < Maxrow; i++)
	{
		for (j = 0; j < Maxcol; j++)
		{
			if (board[i][j] == 0)
			{
				dead(i, j);
			}
			if (board[i][j] == 1)
			{
				count++;
				alive(i, j);
			}
		}
	}
	if (count == 0)
	{
		printf("Sorry that your last game has over because all cells have died.\n");
		printf("We will restart the game for you.\n");
		return 1;
	}
	return 0;
}

int chess(int **board)
{
	int i, j, row, col;
	for (row = 0; row != Maxrow; row++)
	{
		for (col = 0; col != Maxcol; col++)
		{
			if (board[row][col] != 1 && board[row][col] != 0)
			{
				printf("The original-state array hasn't been initialized.\n");
				return -1;
			}
		}
	}
	for (i = 0; i < Maxrow; i++)
	{
		for (j = 0; j < Maxcol; j++)
		{
			if (board[i][j] == 0)
			{
				dead(i, j);
			}
			if (board[i][j] == 1)
			{
				alive(i, j);
			}
		}
	}
	return 0;
}

int judgeNext(int neighbor, int row, int col, int **board)
{
	if (neighbor == 2)
	{
		return board[row][col];
	}
	else if (neighbor == 3)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int main(int argc, char *args[])
{
	// Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		// Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			// Main loop flag
			bool quit = false;

			// Event handler
			SDL_Event e;

			// While application is running
			while (!quit)
			{
				// Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					// User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
				}
				SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
				// Clear screen
				SDL_RenderClear(gRenderer);

				// Render texture to screen
				// SDL_RenderCopy( gRenderer, gTexture, NULL, NULL );
				int i = 0, j = 0, n = 0, row, col;
				int times = 5;
				Maxrow = 5;
				Maxcol = 5;
				// init the world
				int **orgn = (int **)malloc(Maxrow * sizeof(int *));
				int **ret = (int **)malloc(Maxrow * sizeof(int *));
				for (i = 0; i < Maxrow; i++)
				{
					orgn[i] = (int *)malloc(sizeof(int) * Maxcol);
					ret[i] = (int *)malloc(sizeof(int) * Maxcol);
					for (j = 0; j < Maxcol; j++)
					{
						orgn[i][j] = 0;
						ret[i][j] = 0;
					}
				}
				orgn[0][1] = 1;
				orgn[0][3] = 1;
				orgn[1][2] = 1;
				orgn[1][4] = 1;
				orgn[2][1] = 1;
				orgn[2][2] = 1;

				// Display the intial state of the world
				initchess(orgn);
				// Update screen
				SDL_RenderPresent(gRenderer);
				SDL_Delay(1500);

				/*Start the iteration*/
				for (n = 0; n < times; n++)
				{
					// judge the next round
					for (row = 0; row < Maxrow; row++)
					{
						for (col = 0; col < Maxcol; col++)
						{
							int neighbor = 0, c, r;
							for (r = row - 1; r <= row + 1; r++)
								for (c = col - 1; c <= col + 1; c++)
								{
									if (r < 0 || r >= Maxrow)
										continue;
									if (c < 0 || c >= Maxcol)
										continue;
									if (orgn[r][c] == 1)
										neighbor++;
								}
							if (orgn[row][col] == 1)
								neighbor--;
							ret[row][col] = judgeNext(neighbor, row, col, orgn);
						}
					}

					SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
					// Clear screen
					SDL_RenderClear(gRenderer);
					// Display the world
					chess(ret);
					// Update screen
					SDL_RenderPresent(gRenderer);
					SDL_Delay(1500);
					/*judge whether the program will terminate*/
					for (i = 0; i != Maxrow; i++)
					{
						for (j = 0; j != Maxrow; j++)
						{
							if (ret[i][j] == orgn[i][j])
							{
								isFlag = 1;
							}
						}
					}
					if (isFlag == 0)
					{
						printf("The cellular state of the game will no longer change.");
						SDL_Delay(1500);
						SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
						// Clear screen
						SDL_RenderClear(gRenderer);
						break;
					}
					/*update the array*/
					for (i = 0; i != Maxrow; i++)
					{
						for (j = 0; j != Maxcol; j++)
						{
							orgn[i][j] = ret[i][j];
						}
					}	
				}
				for (i = 0; i < Maxcol; i++){
						free(orgn[i]);
						free(ret[i]);
				}
				free(orgn);
				free(ret);
				break;
			}
		}

		// Free resources and close SDL
		closeAll();

		return 0;
	}
}