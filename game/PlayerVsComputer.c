#include <stdio.h>
#include "gobang.h"

void playerVsComputer(void){  //正在开发中...
    int quit = 0;  //表示是否退出，1为退出，0为不退出
    player = 1;  //黑方先落子，所以初始化player为1
    initRecordBoard(); // 初始化一个空棋盘
    innerLayoutToDisplayArray();  // 将心中的棋盘转成用于显示的棋盘
    displayBoard();  // 显示棋盘
    printf("正在开发中...\n");
    mygetline(line, MAXLINE);  // 从键盘读取输入到line中
}

void regret2(void){
    //正在开发中...
}