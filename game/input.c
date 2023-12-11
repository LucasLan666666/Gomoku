// 此文件用于游戏过程中处理玩家的输入
#include <stdio.h>
#include <stdlib.h>
#include "gobang.h"

char line[MAXLINE];  //记录读取到的一行

// 读取一行玩家的输入
void mygetline(char s[], int lim){
    int i, c;
    i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n'){
        s[i++] = c;
    }
    if ((c == '\n')){
        s[i] = '\0';
    }else{
        putchar('\n');
        exit(0);  // 读到EOF直接退出游戏
    }
}

// 比较两个字符串，1表示二者相同，0表示二者不同
int mystrcmp(char *s, char *t){
    int i;
    for (i = 0; s[i] == t[i]; i++)
        if (s[i] == '\0')
            return 1;
    return 0;
}

// 对玩家输入进行判断：如果输入的是合法坐标格式，直接完成转换并储存在数组currentPlayerMoveStone[2]为，同时返回0；如果输入的是quit指令，返回1；如果输入的是regret指令，返回2；如果输入有误，返回-1
int inputCheck(void){
    if (inputToCoordinate() == 0){
        return 0;
    }else if (mystrcmp(line, "quit")){
        return 1;
    }else if (mystrcmp(line, "regret")){
        return 2;
    }else{
        return -1;
    }
}
