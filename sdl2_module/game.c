
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <malloc.h>
#include "stdbool.h"
#include "gameData.h"
#include "gameFunctions.h"
#include "controlFunctions.h"


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
				SDL_RenderClear(gRenderer);
				SDL_RenderPresent(gRenderer);

				char filename[50] = "initstate.txt";
				load(filename);

			}
		}
	}

	return success;
}

void closeAll()
{
	int i;
	// Free the dynamic arrays
	for (i = 0; i < Maxcol; i++)
	{
		free(orgn[i]);
		free(ret[i]);
	}
	free(orgn);
	free(ret);

	// Free loaded image
	SDL_DestroyTexture(gTexture);
	gTexture = NULL;

	// Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	// Quit SDL subsystems
	// IMG_Quit();
	atexit(SDL_Quit);
}

// Display the dead cells
int dead(int row, int col)
{
	if (row >= 0 && row < Maxrow && col >= 0 && col < Maxcol)
	{
		fillRect.x = SCREEN_WIDTH / Maxcol * col;
		fillRect.y = BUTTON_AREA + (SCREEN_HEIGHT - BUTTON_AREA) / Maxrow * row;
		fillRect.w = SCREEN_WIDTH / Maxcol;
		fillRect.h = (SCREEN_HEIGHT - BUTTON_AREA) / Maxrow;
		// Rendering white to fill the rectangle
		SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
		SDL_RenderFillRect(gRenderer, &fillRect);
		return 0;
	}
	else
	{
		return -1;
	}
}

// Display the alive cells
int alive(int row, int col)
{
	if (row >= 0 && row < Maxrow && col >= 0 && col < Maxcol)
	{
		fillRect.x = SCREEN_WIDTH / Maxcol * col;
		fillRect.y = BUTTON_AREA + (SCREEN_HEIGHT - BUTTON_AREA) / Maxrow * row;
		fillRect.w = SCREEN_WIDTH / Maxcol;
		fillRect.h = (SCREEN_HEIGHT - BUTTON_AREA) / Maxrow;
		// Rendering  to fill the rectangle
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
		SDL_RenderFillRect(gRenderer, &fillRect);
		return 0;
	}
	else
	{
		return -1;
	}
}

int initchess()
{
	int i, j, row, col, hor_y, ver_x;
	int count = 0;
	for (row = 0; row != Maxrow; row++)
	{
		for (col = 0; col != Maxcol; col++)
		{
			if (orgn[row][col] != 1 && orgn[row][col] != 0)
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
			if (orgn[i][j] == 0)
			{
				dead(i, j);
			}
			if (orgn[i][j] == 1)
			{
				count++;
				alive(i, j);
			}
		}
	}

	// draw the outline
	for (i = 0; i <= Maxrow; i++)
	{
		hor_y = BUTTON_AREA + (SCREEN_HEIGHT - BUTTON_AREA) / Maxrow * i;
		SDL_SetRenderDrawColor(gRenderer, 209, 206, 220, 0);
		SDL_RenderDrawLine(gRenderer, 0, hor_y, SCREEN_WIDTH, hor_y);
	}
	for (j = 0; j <= Maxcol; j++)
	{
		ver_x = SCREEN_WIDTH / Maxcol * j;
		SDL_SetRenderDrawColor(gRenderer, 209, 206, 220, 0);
		SDL_RenderDrawLine(gRenderer, ver_x, BUTTON_AREA, ver_x, SCREEN_HEIGHT);
	}
	// Update screen
	SDL_RenderPresent(gRenderer);
	if (count == 0)
	{
		printf("Sorry that your last game has over because all cells have died.\n");
		printf("We will restart the game for you.\n");
		return 1;
	}
	return 0;
}

int chess()
{
	int i, j, row, col, hor_y, ver_x;
	for (row = 0; row != Maxrow; row++)
	{
		for (col = 0; col != Maxcol; col++)
		{
			if (ret[row][col] != 1 && ret[row][col] != 0)
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
			if (ret[i][j] == 0)
			{
				dead(i, j);
			}
			if (ret[i][j] == 1)
			{
				alive(i, j);
			}
		}
	}

	// draw the outline
	for (i = 0; i <= Maxrow; i++)
	{
		hor_y = BUTTON_AREA + (SCREEN_HEIGHT - BUTTON_AREA) / Maxrow * i;
		SDL_SetRenderDrawColor(gRenderer, 209, 206, 220, 0);
		SDL_RenderDrawLine(gRenderer, 0, hor_y, SCREEN_WIDTH, hor_y);
	}
	for (j = 0; j <= Maxcol; j++)
	{
		ver_x = SCREEN_WIDTH / Maxcol * j;
		SDL_SetRenderDrawColor(gRenderer, 209, 206, 220, 0);
		SDL_RenderDrawLine(gRenderer, ver_x, BUTTON_AREA, ver_x, SCREEN_HEIGHT);
	}
	// Update screen
	SDL_RenderPresent(gRenderer);
	return 0;
}

int Adjacent(int neighbor, int row, int col, int **board)
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

bool judgeNext()
{
	bool isFlag = false;
	int row, col, i, j;
	int neighbor = 0, c, r;
	for (row = 0; row < Maxrow; row++)
	{
		for (col = 0; col < Maxcol; col++)
		{
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
			ret[row][col] = Adjacent(neighbor, row, col, orgn);
			neighbor = 0;
		}
	}
	/*judge whether the program will terminate*/
	for (row = 0; row != Maxrow; row++)
	{
		for (col = 0; col != Maxrow; col++)
		{
			if (ret[row][col] != orgn[row][col])
			{
				isFlag = true;
			}
		}
	}
	/*update the array*/
	for (i = 0; i != Maxrow; i++)
	{
		for (j = 0; j != Maxcol; j++)
		{
			orgn[i][j] = ret[i][j];
		}
	}
	return isFlag;
}

int load(char filename[50])
{
	FILE *fp = fopen(filename, "r");
	int i, j, temp1, temp2;

	if (fp == NULL)
	{
		printf("Sorry, the file doesn't exist.");
		return -1;
	}
	else
	{
		if (fscanf(fp, "%d%d", &temp1, &temp2) == 2)
		{
			Maxrow = temp1;
			Maxcol = temp2;
			orgn = (int **)malloc(Maxrow * sizeof(int *));
			ret = (int **)malloc(Maxrow * sizeof(int *));
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
		}
		for (i = 0; i < Maxrow; i++)
		{
			for (j = 0; j < Maxcol; j++)
			{
				if (fscanf(fp, "%d  ", &temp1) == 1)
				{
					orgn[i][j] = temp1;
				}
			}
		}
	}
	fclose(fp);
	return 0;
}

int save(char filename[50])
{
	char c = '\n';
	FILE *fp = fopen(filename, "w");
	if (fp == NULL)
	{
		printf("Sorry, the file doesn't exist.");
		return -1;
	}
	int i, j;
	fprintf(fp, "%d%c", Maxrow, c);
	fprintf(fp, "%d%c", Maxcol, c);	
	for (i = 0; i < Maxrow; i++)
	{
		for (j = 0; j < Maxcol; j++)
		{
			fprintf(fp, "%d  ", ret[i][j]);
		}
		fprintf(fp, "%c", c);
	}
	fclose(fp);
	return 0;
}

void gameover()
{
}