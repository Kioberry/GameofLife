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
				gameState = START;
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

	atexit(SDL_Quit);
}

void drawOutline(int ver_x, int hor_y){
	int i, j;
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
	int i, j, row, col, hor_y = 0, ver_x = 0;
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
	drawOutline(ver_x, hor_y);
	return 0;
}

int chess()
{
	int i, j, row, col, hor_y = 0, ver_x = 0;
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

	drawOutline(ver_x, hor_y);
	
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

bool judgeNext(int** orgn, int** ret)
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

int whetherClick()
{
	int num = 0;
	char str[20] = {'\0'};
	printf("Choose one way to initialize the world:\n");
	printf("1.Default Mode\n");
	printf("2.CLick to initialize\n");
	printf("Option: ");
	if (scanf("%s", str) == 1)
	{
		num = atoi(str);
		if (num == 1 || num == 2)
		{
			return num;
		}
		else
		{
			printf("Invalid unput.\n");
			return -1;
		}
	}
	return 0;
}

void MouseClick(int** uorgn, int Mousex, int Mousey)
{
	int row, col, ver_x = 0, hor_y = 0;
	for (row = 0; row < Maxrow; row++)
	{
		for (col = 0; col < Maxcol; col++)
		{
			if (Mousex >= SCREEN_WIDTH / Maxcol * col && Mousex < SCREEN_WIDTH / Maxcol * (col + 1))
			{
				if (Mousey >= BUTTON_AREA + (SCREEN_HEIGHT - BUTTON_AREA) / Maxrow * row && Mousey < BUTTON_AREA + (SCREEN_HEIGHT - BUTTON_AREA) / Maxrow * (row + 1))
				{
					uorgn[row][col] = 1;
					alive(row, col);
				}
			}
		}
	}
	drawOutline(ver_x, hor_y);
	if (Mousey>=0 && Mousey<BUTTON_AREA){
		gameState = UPLAYING;
		return;
	}
}

void draw()
{
	int chosen = 0;
	int** uorgn = NULL;
	// Initialize renderer color
	SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
	SDL_RenderClear(gRenderer);

	switch (gameState)
	{
	case START:
		SDL_Rect destRect1 = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
		SDL_RenderFillRect(gRenderer, &destRect1);
		gTexture = IMG_LoadTexture(gRenderer, START_FILE_NAME);
		SDL_RenderCopy(gRenderer, gTexture, NULL, &destRect1);
		break;
	case MODE:
		chosen = whetherClick();
		if (chosen == -1)
		{
			printf("The game will terminate\n");
			exit(1);
		}
		else
		{
			// switch (chosen)
			// {
			// case 1:
			// 	gameState = FIRST;
			// 	break;
			// case 2:
			// 	int i, j;
			// 	gameState = UFIRST;
			// 	// initialise the orginal array again
			// 	uorgn = (int **)malloc(Maxrow * sizeof(int *));
			// 	for (i = 0; i < Maxrow; i++)
			// 	{
			// 		uorgn[i] = (int *)malloc(sizeof(int) * Maxcol);
			// 		for (j = 0; j < Maxcol; j++)
			// 		{
			// 			uorgn[i][j] = 0;
			// 		}
			// 	}
			// 	break;
			// }
		}
	case FIRST:
		initchess();
		gameState = PLAYING;
		break;
	case UFIRST:
		MouseClick(uorgn,Mousex,Mousey);
	case PLAYING:
		if (!judgeNext(orgn, ret))
		{
			printf("The state of the cells won't change anymore, the program will terminate.\n");
			gameState = OVER;
			return;
		}
		chess();
		break;
	case UPLAYING:
		if (!judgeNext(uorgn, ret))
		{
			printf("The state of the cells won't change anymore, the program will terminate.\n");
			gameState = OVER;
			return;
		}
		chess();
		break;	
	case OVER:
		if (gTexture != NULL)
		{
			SDL_DestroyTexture(gTexture);
			gTexture = NULL;
		}
		SDL_Rect destRect2 = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
		SDL_RenderFillRect(gRenderer, &destRect2);
		gTexture = IMG_LoadTexture(gRenderer, OVER_FILE_NAME);
		SDL_RenderCopy(gRenderer, gTexture, NULL, &destRect2);
		break;
	}

	// Update screen
	SDL_RenderPresent(gRenderer);
}

void eventLoop()
{
	while (true)
	{
		SDL_Event event;

		int begin = SDL_GetTicks();

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				// destroy all
				return;

			case SDL_MOUSEBUTTONDOWN:
				if (gameState == START)
				{
					char filename[50] = "initstate.txt";
					load(filename);
					gameState = MODE;
				}
				if (gameState == UFIRST)
				{
					Mousex = event.button.x;
					Mousey = event.button.y;
				}
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					// destroy all
					return;
				}
			}
		}
		draw();

		int end = SDL_GetTicks();
		int time_ = end - begin;
		int rate = 1000 / FRAMERATE;
		int delay = rate - time_;

		if (delay > 0)
		{
			SDL_Delay(delay);
		}
	}
}