#include <string.h>
#include <malloc.h>
#include "check.h"
#include "../include/gameFunctions.h"

START_TEST(test_game_alive_dead)
{
    char msg[50] = {'\0'};
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
}
END_TEST

START_TEST(test_game_chess_initchess)
{
    int i, j;
    char msg[50] = {'\0'};
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
    //satisfactory situation
    board[1][1] = 1;
    strcpy(msg, "error, initchess(board) != 0 over");
    fail_unless(initchess(board) == 0, msg);
    strcpy(msg, "error, chess(board) != 0 over");
    fail_unless(chess(board) == 0, msg);
}
END_TEST

START_TEST(test_file_load){
    char filename[50], msg[50] = {'\0'};
    // int i, j;
    // int** board;
    // board = (int **)malloc(Maxrow * sizeof(int *));
    // for (i = 0; i < Maxrow; i++)
    // {
    //     board[i] = (int *)malloc(sizeof(int) * Maxcol);
    //     for(j=0;j<Maxcol;j++){
    //         board[i][j] = 0;
    //     }
    // }
    // board[1][1] = 1;
    // /*Tests for load(char filename[50]) function and save(char filename[50] function)*/
    // //declared but not uninitialized char array
    // strcpy(msg, "error, load(filename) != -1 over");
    // fail_unless( load(filename) == -1, msg);
    // strcpy(msg, "error, save(filename, board) != -1 over");
    // fail_unless( save(filename, board) == -1, msg);
    // //an initialized array with invalid filename
    // strcpy(filename, "1.txt");
    // strcpy(msg, "error, load(filename) != -1 over");
    // fail_unless( load(filename) == 0, msg);
    // strcpy(msg, "error, save(filename, board) != 0 over");
    // fail_unless( save(filename, board) == -1, msg);
    // //satisfactory situation
    // strcpy(filename, "initstate.txt");
    // strcpy(msg, "error, load(filename) != 0 over");
    // fail_unless( load(filename) == 0, msg);
    // strcpy(msg, "error, save(filename, board) != 0 over");
    // fail_unless( save(filename, board) == 0, msg);
    testsave(filename);
    strcpy(msg, "error, testsave(filename) != 0 over");
    fail_unless(testsave(filename) == 0, msg);


   
}
END_TEST

Suite *make_unit_suite1(void)
{
    Suite *s1 = suite_create("Game");      //创建一个名为Game的 Suite
    TCase *tc_bao1 = tcase_create("Core"); //创建一个名为Core的a test  case（Tcase）

    suite_add_tcase(s1, tc_bao1);                   //将a test  case添加到Tcase（bao1）中
    tcase_add_test(tc_bao1, test_game_alive_dead); //将a test  funtion （aaa） 添加到 a test  case（bao2）中
    tcase_add_test(tc_bao1, test_game_chess_initchess);

    return s1; //返回一个Suite的地址。
}

Suite *make_unit_suite2(void)
{
    
    Suite *s2 = suite_create("File");      //创建一个名为bao1的 Suite
    TCase *tc_bao2 = tcase_create("fCore"); //创建一个名为bao2的a test  case（Tcase）

    suite_add_tcase(s2, tc_bao2);                   //将a test  case添加到Tcase（bao1）中
    tcase_add_test(tc_bao2, test_file_load); //将a test  funtion （aaa） 添加到 a test  case（bao2）中

    return s2; //返回一个Suite的地址。
}
