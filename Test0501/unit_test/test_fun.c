#include <string.h>
#include <malloc.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "check.h"
#include "../include/gameFunctions.h"

START_TEST(test_game_alive_dead)
{
    char msg[50] = {'\0'};
    printf("Running test case 1: test_game_alive_dead\n");
    /*Tests for the alive(row, col) function*/
    // satisfactory situations including edge cases
    strcpy(msg, "error, alive(1, 2) != 0 over");
    fail_unless(alive(1, 2) == 0, msg);
    strcpy(msg, "error, alive(1, 0) != 0 over");
    fail_unless(alive(1, 0) == 0, msg);
    strcpy(msg, "error, alive(0, 2) != 0 over");
    fail_unless(alive(0, 2) == 0, msg);
    strcpy(msg, "error, alive(0, 0) != 0 over");
    fail_unless(alive(0, 0) == 0, msg);
    // situations when integers out of bounds
    strcpy(msg, "error, alive(-1, -2) != -1 over");
    fail_unless(alive(-1, -2) == -1, msg);
    strcpy(msg, "error, alive(Maxrow, Maxcol+1) != -1 over");
    fail_unless(alive(Maxrow, Maxcol + 1) == -1, msg);

    /*Tests for the dead(row, col) function*/
    // satisfactory situations including edge cases
    strcpy(msg, "error, dead(1, 2) != 0 over");
    fail_unless(dead(1, 2) == 0, msg);
    strcpy(msg, "error, dead(1, 0) != 0 over");
    fail_unless(dead(1, 0) == 0, msg);
    strcpy(msg, "error, dead(0, 2) != 0 over");
    fail_unless(dead(0, 2) == 0, msg);
    strcpy(msg, "error, dead(0, 0) != 0 over");
    fail_unless(dead(0, 0) == 0, msg);
    // situations when integers out of bounds
    strcpy(msg, "error, dead(-1, -2) != -1 over");
    fail_unless(dead(-1, -2) == -1, msg);
    strcpy(msg, "error, dead(MAX, MAX+1) != -1 over");
    fail_unless(dead(Maxrow, Maxcol) == -1, msg);
    printf("\n");
}
END_TEST

START_TEST(test_game_chess_initchess)
{
    int i, j;
    char msg[50] = {'\0'};
    printf("Running test case 2: test_game_chess_initchess\n");
    /*Tests for initchess(int** orgn) function & chess(int** ret) function*/
    // situation when the pointer is NULL
    int **board = NULL;
    strcpy(msg, "error, initchess(board) != -1 over");
    fail_unless(initchess(board) == -1, msg);
    fail_unless(chess(board) == -1, msg);
    // situation when the array elements haven't been initialized
    board = (int **)malloc(Maxrow * sizeof(int *));
    for (i = 0; i < Maxrow; i++)
    {
        board[i] = (int *)malloc(sizeof(int) * Maxcol);
    }
    fail_unless(initchess(board) == -1, msg);
    fail_unless(chess(board) == -1, msg);
    // situation when all the array elements are 0 (designed especially for function initchess(int** orgn))
    for (i = 0; i < Maxrow; i++)
    {
        for (j = 0; j < Maxcol; j++)
        {
            board[i][j] = 0;
        }
    }
    strcpy(msg, "error, initchess(board) != 1 over");
    fail_unless(initchess(board) == 1, msg);
    strcpy(msg, "error, chess(board) != 0 over");
    fail_unless(chess(board) == 0, msg);
    // satisfactory situation
    board[1][1] = 1;
    strcpy(msg, "error, initchess(board) != 0 over");
    fail_unless(initchess(board) == 0, msg);
    strcpy(msg, "error, chess(board) != 0 over");
    fail_unless(chess(board) == 0, msg);
    printf("\n");
}
END_TEST

START_TEST(test_game_adjacent)
{
    char msg[50] = {'\0'};
    char filename[50] = "src/initstate.txt";
    printf("Running test case 3: test_game_adjacent\n");
    // situations when the int pointer is NULL
    strcpy(msg, "error, Adjacent(1, 1, 2, NULL) != -1 over");
    fail_unless(Adjacent(1, 1, 2, NULL) == -1, msg);
    strcpy(msg, "error, Adjacent(-1, 1, 0, NULL) != -1 over");
    fail_unless(Adjacent(-1, 1, 1, NULL) == -1, msg);
    strcpy(msg, "error, Adjacent(0, 0, 0, NULL) != -1 over");
    fail_unless(Adjacent(-1, -2, Maxcol, NULL) == -1, msg);

    // situations when all the parameters are valid, the return value
    // is decided by the value of neighbor
    load(filename);
    strcpy(msg, "error, Adjacent(2, 1, 2, orgn) != 1 over");
    fail_unless(Adjacent(2, 1, 2, orgn) == 1, msg);
    strcpy(msg, "error, Adjacent(2, 0, 0, orgn) != 0 over");
    fail_unless(Adjacent(2, 0, 0, orgn) == 0, msg);
    strcpy(msg, "error, Adjacent(3, 1, 2, orgn) != 1 over");
    fail_unless(Adjacent(3, 1, 2, orgn) == 1, msg);
    strcpy(msg, "error, Adjacent(3, 0, 0, orgn) != 1 over");
    fail_unless(Adjacent(3, 0, 0, orgn) == 1, msg);
    strcpy(msg, "error, Adjacent(8, 1, 2, orgn) != 0 over");
    fail_unless(Adjacent(8, 1, 2, orgn) == 0, msg);
    strcpy(msg, "error, Adjacent(8, 0, 0, orgn) != 0 over");
    fail_unless(Adjacent(8, 0, 0, orgn) == 0, msg);

    // situations when the int pointer is satisfactory but int row(col)
    // or int neighbor is invalid
    strcpy(msg, "error, Adjacent(9, 1, 2, orgn) != -1 over");
    fail_unless(Adjacent(9, 1, 2, orgn) == -1, msg);
    strcpy(msg, "error, Adjacent(-1, 1, 2, orgn) != -1 over");
    fail_unless(Adjacent(-1, 1, 2, orgn) == -1, msg);
    strcpy(msg, "error, Adjacent(2, -1, 2, orgn) != -1 over");
    fail_unless(Adjacent(2, -1, 2, orgn) == -1, msg);
    strcpy(msg, "error, Adjacent(2, Maxrow+1, 2, orgn) != -1 over");
    fail_unless(Adjacent(2, Maxrow + 1, 2, orgn) == -1, msg);
    printf("\n");
}
END_TEST

START_TEST(test_game_judgenext)
{
    char msg[50] = {'\0'}, filename[50];
    int i, j;
    printf("Running test case 4: test_game_judgenxt\n");
    strcpy(filename, "src/initstate.txt");
    load(filename);
    strcpy(msg, "error, judgeNext(orgn, ret) != true, over");
    fail_unless(judgeNext(orgn, ret) == true, msg);
    strcpy(filename, "src/test.txt");
    load(filename);
    strcpy(msg, "error, judgeNext(orgn, ret) != false, over");
    fail_unless(judgeNext(orgn, ret) == false, msg);
    printf("\n");
}
END_TEST

START_TEST(test_file_load_save)
{
    char filename[50] = {'\0'}, msg[50] = {'\0'};
    int i, j;
    printf("Running test case 1: test_file_load_save\n");
    /*Tests for load(char filename[50]) function and save(char filename[50] function)*/
    // declared but unasssigned char array
    strcpy(msg, "error, load(filename) != -1 over");
    fail_unless(load(filename) == -1, msg);
    strcpy(msg, "error, save(filename) != -1 over");
    fail_unless(save(filename) == -1, msg);
    // an initialized array with invalid filename
    strcpy(filename, "1.txt");
    strcpy(msg, "error, load(filename) != -1 over");
    fail_unless(load(filename) == -1, msg);
    strcpy(msg, "error, save(filename) != 0 over");
    fail_unless(save(filename) == -1, msg);
    // satisfactory situation
    strcpy(filename, "src/initstate.txt");
    strcpy(msg, "error, load(filename) != 0 over");
    fail_unless(load(filename) == 0, msg);
    for (i = 0; i < Maxrow; i++)
    {
        for (j = 0; j < Maxcol; j++)
        {
            ret[i][j] = orgn[i][j];
        }
    }
    strcpy(msg, "error, save(filename) != 0 over");
    fail_unless(save(filename) == 0, msg);
    strcpy(filename, "1.txt");
    strcpy(msg, "error, save(filename) != 0 over");
    fail_unless(save(filename) == 0, msg);
    printf("\n");
}
END_TEST

START_TEST(test_SDL_MouseClick)
{
    char filename[50] ="src/initstate.txt", msg[50] = {'\0'};
    SDL_Point point = {1, 1};
    printf("Running test case 5: test_SDL_MouseClick\n");
    //A null int pointer with satisfactory SDL_Point structure
    strcpy(msg, "error, MouseClick(NULL, point) != -1 over");
    fail_unless(MouseClick(NULL, point) == -1, msg);
    //A null int pointer with invalid SDL_Point structure
    point.x = SCREEN_WIDTH + 1;
    point.y = SCREEN_HEIGHT;
    fail_unless(MouseClick(NULL, point) == -1, msg);
    //A satisfactory pointer with invalid SDL_Point structure
    load(filename);
    strcpy(msg, "error, MouseClick(uorgn, point) != -1 over");
    fail_unless(MouseClick(uorgn, point) == -1, msg);
    // satisfactory situation
    point.x = SCREEN_WIDTH / 2;
    point.y = SCREEN_HEIGHT / 3;
    strcpy(msg, "error, MouseClick(uorgn, point) != 0 over");
    fail_unless(MouseClick(uorgn, point) == 0, msg);
    printf("\n");
}
END_TEST

Suite *make_unit_suite1(void)
{
    Suite *s1 = suite_create("Game");      // Create a test suite called Game
    TCase *tc_bao1 = tcase_create("Core"); // Create a test case（Tcase）called Core

    suite_add_tcase(s1, tc_bao1);                  // Add a Tcase(Core) the test suite(Game)
    tcase_add_test(tc_bao1, test_game_alive_dead); // add a test function to the Tcase(Core)
    tcase_add_test(tc_bao1, test_game_chess_initchess);
    tcase_add_test(tc_bao1, test_game_adjacent);
    tcase_add_test(tc_bao1, test_game_judgenext);
    tcase_add_test(tc_bao1, test_SDL_MouseClick);

    return s1; // Return the address of the Suite
}

Suite *make_unit_suite2(void)
{

    Suite *s2 = suite_create("File");       ////Create a test suite called File
    TCase *tc_bao2 = tcase_create("fCore"); // Create a test case（Tcase）called fCore

    suite_add_tcase(s2, tc_bao2);                 // Add a Tcase(fCore) the test suite(File)
    tcase_add_test(tc_bao2, test_file_load_save); ////add a test function to the Tcase(fCore)

    return s2; // Return the address of the Suite
}
