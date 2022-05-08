#include <stdio.h>
#include <stdlib.h>
#define N 10

void input_str(char* str) {
	for (int i = 0, ch = '\0'; ch != '\n'; ++i) {
		ch = getchar();
		if (i >= N) {//当超出字符串长度时, 继续接受键盘输入的字符,直到输入\n为止
			//这是为了防止字符串输入完成后输入的字符会被下一个需要输入的数据接收
			continue;
		}
		if (ch == '\n' || i == N - 1) {
			str[i] = '\0';
			continue;
		}
		str[i] = ch;
	}
}