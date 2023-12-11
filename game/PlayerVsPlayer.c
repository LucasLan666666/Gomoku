// 本文件包含双人对战相关内容
#include <stdio.h>
#include <ctype.h>
#include "gobang.h"

void playerVsPlayer(void){
    int quit = 0;  //表示是否退出，1为退出，0为不退出
    int check;  // 储存读取输入的相关信息
    player = 1;  //黑方先落子，所以初始化player为1
    initRecordBoard(); // 初始化一个空棋盘
    while (quit == 0){
        innerLayoutToDisplayArray();  // 将心中的棋盘转成用于显示的棋盘
        displayBoard();  // 显示棋盘
        mygetline(line, MAXLINE);  // 从键盘读取输入到line中
        while ((check = inputCheck()) == -1){  // 对玩家输入进行判断：如果输入的是坐标，返回0；如果输入的是quit指令，返回1；如果输入的是regret指令，返回2；如果输入有误，返回-1
            printf("你的输入有误，请重新输入：");
            mygetline(line, MAXLINE);
        }
        switch (check){
        case 0:
            coordinateToMoveStone();  // 将坐标转化为棋盘上的落子
            break;
        case 1:
            quit = 1;  // 退出while循环
            break;
        case 2:
            regret1();  // 还没写
            break;
        default:
            break;
        }
    }
}

void regret1(void){
    //正在开发中...
}