#include <stdio.h>
#include <SDL2/SDL.h>
#include "../include/gameData.h"
#include "../include/gameFunctions.h"

int Maxrow = 6, Maxcol = 6;
// int Mousex = 0, Mousey = 0;
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

int testsave(char filename[50])
{
	FILE *fp = NULL;
	int i = 0;
	unsigned char ch = filename[i];
	while (filename[i])
	{
		if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		{
			i++;
			continue;
		}
		else
		{
			if (ch >= '0' && ch <= '9')
			{
				i++;
				continue;
			}
			else{
				printf("Invalid input of file name.\n");
				return -1;
			}
		}
	}
	//fp = fopen(filename, "w");
	// if (fp == NULL)
	// {
	// 	printf("Sorry, the file doesn't exist.\n");
	// 	return -1;
	// }
	fclose(fp);
	return 0;
}

int save(char filename[50], int **board)
{
	char c = '\n';
	FILE *fp = fopen(filename, "w");
	if (fp == NULL)
	{
		printf("Sorry, the file doesn't exist.\n");
		return -1;
	}
	int i, j;
	fprintf(fp, "%d%c", Maxrow, c);
	fprintf(fp, "%d%c", Maxcol, c);
	for (i = 0; i < Maxrow; i++)
	{
		for (j = 0; j < Maxcol; j++)
		{
			fprintf(fp, "%d  ", board[i][j]);
		}
		fprintf(fp, "%c", c);
	}
	fclose(fp);
	return 0;
}