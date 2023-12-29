// 本文件包含双人对战相关内容
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "gomoku.h"

void playerVsPlayer(void){
    int quit = 0;  //表示是否退出，1为退出，0为不退出
    int check;  // 储存读取输入的相关信息
    player = 1;  //黑方先落子，所以初始化player为1
    stepNum = 0;  // 初始化步数为0
    initRecordBoard(); // 初始化一个空棋盘

    while (quit == 0){
        innerLayoutToDisplayArray();  // 将心中的棋盘转成用于显示的棋盘
        displayBoard();  // 显示棋盘

        // 输出当前等待落子的玩家
        printf("    现在请%s落子：\n\t", (player == 1) ? "黑方" : "白方");

        mygetline();  // 从键盘读取输入到line中

        // 对玩家输入进行判断：如果输入的是坐标，返回0；如果输入的是quit指令，返回1；如果输入的是regret指令，返回2；如果输入有误，返回-1
        while ((check = inputCheckInGame()) == -1){
            printf("    你的输入有误，请重新输入：\n\t");
            mygetline();
        }
        switch (check){
        case 0:
            coordinateToPlaceStone();  // 将坐标转化为棋盘上的落子
            if (gameRecord && readWritePermission){  // 判断是否开启记谱模式，以及是否有读写权限
                recordGameRoundToLocal();  // 记录棋谱到本地
            }
            stepNum++;  // 步数+1（现在才回归正常步数）
            if (judgeWin() != 0){  // 判断是否有玩家获胜
                innerLayoutToDisplayArray();
                displayBoard();  // 显示棋盘
                printf("恭喜%s获胜！\n", (player == 1) ? "白方" : "黑方");  // 因为一方落子瞬间player会反转，所以这里要取反
                printf("输入任意内容返回主页\n");
                mygetline();
                quit = 1;
            }
            break;
        case 1:
            quit = 1;  break;  // 退出while循环
        case 2:
            regret1(); break;
        default:
            break;
        }
    }
}

// 人人对战模式的悔棋模式
void regret1(void){
    // 犹豫要不要写，如果写了悔棋模式，怎么记谱还没想好
}