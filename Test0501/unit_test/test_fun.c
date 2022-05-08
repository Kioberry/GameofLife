#include "check.h"

#include "../include/alive.h"
#include "../include/dead.h"  //头文件相对路径
#include "../include/utility.h" 
#include "../include/game.h"

#define MAX 5

START_TEST(test_game_alive)
{
    fail_unless(alive(1, 2) == 0, "error, alive(1, 2) != 0 over");
    fail_unless(alive(1, 0) == 0, "error, alive(1, 0) != 0 over");
    fail_unless(alive(0, 2) == 0, "error, alive(0, 2) != 0 over");
    fail_unless(alive(0, 0) == 0, "error, alive(0, 0) != 0 over");
    //如果add(1, 4) == 5的话，就成功，否则输出后面的字符串。
    fail_unless(alive(-1, -2) == -1, "error, alive(1, 2) != -1 over");
    fail_unless(alive(MAX, MAX+1) == -1, "error, alive(MAX, MAX+1) != -1 over");
    //turn the parameter to string
    fail_unless(alive("ahha", "3") == -1, "error, alive(\"ahha\", \"3\") != -1 over");
}
END_TEST

START_TEST(test_game_dead)
{
    fail_unless(dead(1, 2) == 0, "error, dead(1, 2) != 0 over");
    fail_unless(dead(1, 0) == 0, "error, dead(1, 0) != 0 over");
    fail_unless(dead(0, 2) == 0, "error, dead(0, 2) != 0 over");
    fail_unless(dead(0, 0) == 0, "error, dead(0, 0) != 0 over");
    //如果add(1, 4) == 5的话，就成功，否则输出后面的字符串。
    fail_unless(dead(-1, -2) == -1, "error, dead(-1, -2) != -1 over");
    fail_unless(dead(MAX, MAX+1) == -1, "error, dead(MAX, MAX+1) != -1 over");
     //turn the parameter to string
    fail_unless(dead("ahha", "3") == -1, "error, alive(\"ahha\", \"3\") != -1 over");
}
END_TEST

START_TEST(test_game){
    int a[MAX][MAX], i=0, j=0;
    fail_unless(initchess(a) == -1, "error, initchess(a) != -1 over");
    fail_unless(chess(a) == -1, "error, chess(a) != -1 over");
    for (i=0; i<MAX; i++){
        for (j=0; j<MAX; j++){
            a[i][j] = 0;
        }
    }
    fail_unless(initchess(a) == 1, "error, initchess(a) != 1 over");
    fail_unless(chess(a) == 0, "error, chess(a) != 0 over");
    a[1][1] = 1;
    fail_unless(initchess(a) == 0, "error, initchess(a) != 0 over");
    fail_unless(chess(a) == 0, "error, chess(a) != 0 over");
}
END_TEST

START_TEST(test_game_chess){
    
    
}
END_TEST
Suite *make_unit_suite(void)
{
    Suite *s = suite_create("Game");          //创建一个名为bao1的 Suite
    TCase *tc_bao = tcase_create("Core");   //创建一个名为bao2的a test  case（Tcase）

    suite_add_tcase(s, tc_bao);    //将a test  case添加到Tcase（bao1）中
    tcase_add_test(tc_bao, test_game_alive);     //将a test  funtion （aaa） 添加到 a test  case（bao2）中
    tcase_add_test(tc_bao, test_game_dead);
    tcase_add_test(tc_bao, test_game);

    return s;            //返回一个Suite的地址。
}
