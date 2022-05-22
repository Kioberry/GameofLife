#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "../include/gameData.h"
#include "../include/gameFunctions.h"

int Maxrow = 6, Maxcol = 6;

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int BUTTON_AREA = 80;

int **orgn = NULL;
int **uorgn = NULL;
int **ret = NULL;

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
		printf("Invalid input of row or col.\n");
		return -1;
	}
}

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
		printf("Invalid input of row or col.\n");
		return -1;
	}
}

/*Display the initial state of chessboard*/
int initchess(int **orgn)
{
	int i, j, row, col, hor_y = 0, ver_x = 0;
	int count = 0;
	if (orgn == NULL)
	{
		printf("Sorry, the array pointer is NULL.\n");
		return -1;
	}
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
	if (count == 0)
	{
		printf("All the cells have died in the last game, we will restart the game for you.\n");
		return 1;
	}
	// draw the outline
	// drawOutline(ver_x, hor_y);
	return 0;
}

/*Display the result state of chessboard every evolution*/
int chess(int **ret)
{
	int i, j, row, col, hor_y = 0, ver_x = 0;
	if (ret == NULL)
	{
		printf("Sorry, the array pointer is NULL.\n");
		return -1;
	}
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

	// drawOutline(ver_x, hor_y);

	return 0;
}

int load(char filename[50])
{
	FILE *fp = fopen(filename, "r");
	int i, j, temp1, temp2;

	if (fp == NULL)
	{
		printf("Sorry, the file doesn't exist.\n");
		orgn = NULL;
		uorgn = NULL;
		ret = NULL;
		return -1;
	}

	fseek(fp, 0, SEEK_END);
	int flen = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	if (flen == 0){
		printf("An empty file with no data.\n");
		return -1;
	}
	else
	{
		if (fscanf(fp, "%d%d", &temp1, &temp2) == 2)
		{
			Maxrow = temp1;
			Maxcol = temp2;
			orgn = (int **)malloc(Maxrow * sizeof(int *));
			uorgn = (int **)malloc(Maxrow * sizeof(int *));
			ret = (int **)malloc(Maxrow * sizeof(int *));
			for (i = 0; i < Maxrow; i++)
			{
				orgn[i] = (int *)malloc(sizeof(int) * Maxcol);
				uorgn[i] = (int *)malloc(sizeof(int) * Maxcol);
				ret[i] = (int *)malloc(sizeof(int) * Maxcol);
				for (j = 0; j < Maxcol; j++)
				{
					orgn[i][j] = 0;
					uorgn[i][j] = 0;
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
		printf("Sorry, the file doesn't exist.\n");
		return -1;
	}
	if (ret == NULL){
		printf("The previous file loading is unsuccessfull, unable to store date to the file.\n");
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

int Adjacent(int neighbor, int row, int col, int **board)
{
	if (neighbor < 0 || neighbor > 8 || row < 0 || row >= Maxrow\
	|| col < 0 || col >= Maxcol || board == NULL)
	{
		printf("There exists invalid formal parameters, unable to continue.\n");
		return -1;
	}
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

bool judgeNext(int **orgn, int **ret)
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
	if (isFlag == false){
		printf("The state of the cells won't change anymore, the program will terminate.\n");
	}
	return isFlag;
}

void drawOutline(int ver_x, int hor_y)
{
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

void loadIMG(SDL_Rect rect, const char *filename)
{
	if (gTexture != NULL)
	{
		SDL_DestroyTexture(gTexture);
		gTexture = NULL;
	}
	SDL_RenderFillRect(gRenderer, &rect);
	gTexture = IMG_LoadTexture(gRenderer, filename);
	SDL_RenderCopy(gRenderer, gTexture, NULL, &rect);
}

int MouseClick(int **uorgn, SDL_Point pos)
{
	if (uorgn == NULL || pos.x<0 || pos.x>SCREEN_WIDTH ||pos.y<0 || pos.y>SCREEN_HEIGHT){
		printf("Invalid int array or SDL_Point.\n");
		return -1;
	}
	int row, col, ver_x = 0, hor_y = 0;
	// Judge whether the cell has been clicked
	for (row = 0; row < Maxrow; row++)
	{
		for (col = 0; col < Maxcol; col++)
		{
			dead(row, col);
			if (SDL_PointInRect(&pos, &fillRect))
			{
				uorgn[row][col] = 1;
			}
		}
	}
	// Display all the cells after every click
	for (row = 0; row < Maxrow; row++)
	{
		for (col = 0; col < Maxcol; col++)
		{
			if (uorgn[row][col] == 1)
			{
				alive(row, col);
			}
		}
	}

	if (gTexture != NULL)
	{
		SDL_DestroyTexture(gTexture);
		gTexture = NULL;
	}
	SDL_Rect destRect3 = {0, 0, SCREEN_WIDTH, BUTTON_AREA};
	SDL_RenderFillRect(gRenderer, &destRect3);
	gTexture = IMG_LoadTexture(gRenderer, CLICK_FILE_NAME);
	SDL_RenderCopy(gRenderer, gTexture, NULL, &destRect3);
	// Draw the outline
	drawOutline(ver_x, hor_y);
	if (pos.y > 0 && pos.y < BUTTON_AREA)
	{
		gameState = UPLAYING;
		return 0;
	}
	return 0;
}