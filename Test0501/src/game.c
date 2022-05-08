#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/alive.h"
#include "../include/dead.h"
#include "../include/utility.h"





#define MAX 5 //每行格子數

int count = 0, row, col, orgn[MAX][MAX], ret[MAX][MAX];
int alive(int row, int col) {
	if (row >= 0 && row < MAX && col >= 0 && col < MAX) {
		return 0;
	}
	else {
		printf("Invalid parameters of row and col.\n");
		return -1;
	}
}

int dead(int row, int col) {
	if (row >= 0 && row < MAX && col >= 0 && col < MAX) {
		return 0;
	}
	else {
		printf("Invalid parameters of row and col.\n");
		return -1;
	}
}

/*Display the initial state of chessboard*/
int initchess(int board[MAX][MAX]) {
	int cont = 0;
	for (row = 0; row != MAX; row++) {
		for (col = 0; col != MAX; col++) {
			if (board[row][col] != 1 && board[row][col] != 0){
				printf("The original-state array hasn't been initialized.\n");
				return -1;
			}
		}
	}
	//printf("棋盤如下：\n");
	for (row = 0; row != MAX; row++) {
		for (col = 0; col != MAX; col++) {
			//printf("%d ", board[row][col]);
			if (board[row][col] == 1){
				cont++;
			}
		}
		//printf("\n");
	}
	if (cont == 0){
		printf("Sorry that your last game has over because all cells have died.\n");
		printf("We will restart the game for you.\n");
		return 1;
	}
	return 0;

	
}
/*Display the result state of chessboard every evolution*/
int chess(int board[MAX][MAX]) {
	for (row = 0; row != MAX; row++) {
		for (col = 0; col != MAX; col++) {
			if (board[row][col] != 1 && board[row][col] != 0){
				printf("The result-state array hasn't been initialized.\n");
				return -1;
			}
		}
	}
	//printf("棋盤如下：\n");
	for (row = 0; row != MAX; row++) {
		for (col = 0; col != MAX; col++) {
			//printf("%d ", board[row][col]);
		}
		//printf("\n");
	}
	return 0;
}

int whetherChoose() {
	int ch = 0;
	int tryNum = 0;
	char chosen = '\0';
	char counts[20] = { '\0' };

	printf("-----The Game of Life------\n");
	while (tryNum <= 3) {
		printf("Do you want to choose the number of iterations?(Y/N): ");
		scanf("%c", &chosen);
		while ((ch = getchar()) != '\n') {
			;
		}
		chosen = toupper(chosen);
		if (chosen == 'Y') {
			printf("Please enter the number of steps: ");
			for (;;) {
				input_str(counts);
				count = atoi(counts);
				if (count <= 0) {
					printf("Invalid input of steps, the number cannot be string or integer that is smaller than 1 ");
				}
				else {
					printf("OK, the program will last %d iterations", count);
					break;
				}
				memset(counts, 0, 20);
			}
			break;
		}
		if (chosen == 'N') {
			printf("OK, the the program will keep evolving until it is terminate");
			break;
		}
		else {
			printf("Invalid choice, try again\n");
		}
		chosen = '\0';
		tryNum++;
	}
	if (chosen == 'Y' || chosen == 'N') {
		return 0;
	}
	else {
		printf("Sorry that you have tried 3 times invalid input, back to the main screen");
		return -1;
	}
}

void game() {
	int i = 0;
	int isFlag = 0;
	/*if life is alive color is balck*/
	//寫讀文件中數據
	
	
	/*init the life array*/
	for (row = 0; row < MAX; row++) {
		for (col = 0; col < MAX; col++) {
			orgn[row][col] = 0;
			ret[row][col] = 0;
		}
	}
	//load("state.txt");
	orgn[0][1] = 1;
	orgn[0][3] = 1;
	orgn[1][2] = 1;
	orgn[1][4] = 1;
	orgn[2][1] = 1;
	orgn[2][2] = 1;


	initchess(orgn);
	fflush(stdout);
	sleep(2);//Linux下為sleep(2)小寫
	system("cls");

	//whetherChoose();
	/*Start the game*/
	for (i = 0; i < count; i++) {
		int cells = 0; //本輪人口數
		for (row = 0; row != MAX; row++) {
			for (col = 0; col != MAX; col++)
			{
				/*if (ret[row][col] == 1) {
					alive(row, col);
				}
				if (ret[row][col] == 0) {
					dead(row, col);
				}*/
				cells += ret[row][col];
			}
		}	
		/*Judge the next round of life*/
		for (row = 0; row != MAX; row++) {
			for (col = 0; col != MAX; col++) {
				if (row == 0 && col == 0) {
					switch (orgn[0][1] + orgn[1][1] + orgn[1][0]) 
					{
						case 3: 
							ret[row][col] = 1; 
							break;
						case 2: 
							ret[row][col] = orgn[row][col]; 
							break;
						default: 
							ret[row][col] = 0;
					}
				} 
				if (row == 0 && col == MAX-1) {
					switch (orgn[0][MAX-2] + orgn[1][MAX-2] + orgn[1][MAX-1])
					{
					case 3:
						ret[row][col] = 1;
						break;
					case 2:
						ret[row][col] = orgn[row][col];
						break;
					default:
						ret[row][col] = 0;
					}
				}
				if (row == MAX-1 && col == 0) {
					switch (orgn[MAX-2][0] + orgn[MAX-2][1] + orgn[MAX-1][1])
					{
					case 3:
						ret[row][col] = 1;
						break;
					case 2:
						ret[row][col] = orgn[row][col];
						break;
					default:
						ret[row][col] = 0;
					}
				}
				if (row == MAX-1 && col == MAX-1) {
					switch (orgn[MAX-1][MAX-2] + orgn[MAX-2][MAX-1] + orgn[MAX-2][MAX-2])
					{
					case 3:
						ret[row][col] = 1;
						break;
					case 2:
						ret[row][col] = orgn[row][col];
						break;
					default:
						ret[row][col] = 0;
					}
				}
				else {
					switch ((orgn[row - 1][col - 1] + orgn[row - 1][col] + orgn[row - 1][col + 1]
						+ orgn[row][col - 1] + orgn[row][col + 1]
						+ orgn[row + 1][col - 1] + orgn[row + 1][col] + orgn[row + 1][col + 1]))
					{
					case 3: 
						ret[row][col] = 1; 
						break;
					case 2: 
						ret[row][col] = orgn[row][col];
						break;
					default: 
						ret[row][col] = 0;
					}
					/*end switch*/
				}
			}
		}
		chess(ret);
		fflush(stdout);
		sleep(2);//Linux下為sleep(2)小寫
		system("cls");
		/*judge whether the program will terminate*/
		for (row = 0; row != MAX; row++) {
			for (col = 0; col != MAX; col++) {
				if (ret[row][col] == orgn[row][col]) {
					isFlag = 1;
				}
			}
		}
		if (isFlag == 0) {
			printf("The cellular state of the game will no longer change.");
			fflush(stdout);
			sleep(2);//Linux下為sleep(2)小寫
			system("cls");
			break;
		}
		/*update the array*/
		for (row = 0; row != MAX; row++) {
			for (col = 0; col != MAX; col++) {
				orgn[row][col] = ret[row][col];
			}		
		}
			
	}
	printf("Thank you for playing the game!Bye!");
}