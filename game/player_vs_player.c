// 本文件包含双人对战相关内容
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "gomoku.h"

void playerVsPlayer(void){
    int quit = NO;  //表示是否退出
    int regret = NO;  // 表示是否悔棋
    int check;  // 储存读取输入的相关信息
    player = BLACK;  //黑方先落子，所以初始化player为1
    stepNum = 0;  // 初始化步数为0
    initRecordBoard(); // 初始化一个空棋盘

    while (quit == NO){
        innerLayoutToDisplayArray();  // 将心中的棋盘转成用于显示的棋盘
        displayBoard();  // 显示棋盘

        if (stepNum == 0 && regret == YES){
            printf("    已经是第一步，无法悔棋！\n");
        }else if (stepNum > 0 && regret == YES){
            printf("    悔棋成功！\n");
        }
        regret = NO;

        // 输出当前等待落子的玩家
        printf("    现在请%s落子：\n\t", (player == BLACK) ? "黑方" : "白方");

        mygetline();  // 从键盘读取输入到line中

        // 对玩家输入进行判断：如果输入的是坐标，返回 0；如果输入的是 quit 指令，返回 1；如果输入的是 regret 指令，返回 2；如果输入有误，返回 -1
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
            if (judgeWin() != NOBODY){  // 判断是否有玩家获胜
                innerLayoutToDisplayArray();
                displayBoard();  // 显示棋盘
                printf("    恭喜%s获胜！\n", (player == BLACK) ? "白方" : "黑方");  // 因为一方落子瞬间player会反转，所以这里要取反
                printf("    输入任意内容返回主页\n");
                mygetline();
                quit = YES;
            }
            // 步数+1
            stepNum++;
            break;
        case 1:
            quit = YES;  break;  // 退出while循环
        case 2:
            regret1(); regret = YES; break;
        default:
            break;
        }
    }
}

// 人人对战模式的悔棋模式
void regret1(void){
    if (stepNum != 0){
        // 步数-1
        stepNum--;
        // 将上一步落子清除
        arrayForInnerBoardLayout[stepRecord[stepNum].x][stepRecord[stepNum].y].current = 0;
        arrayForInnerBoardLayout[stepRecord[stepNum].x][stepRecord[stepNum].y].player = 0;
        for (int k = 0; k < 8; k++){
            arrayForInnerBoardLayout[stepRecord[stepNum].x][stepRecord[stepNum].y].direction[k] = 0;
        }
        // 转换为上一个玩家
        player = (player == BLACK) ? WHITE : BLACK;
        if (gameRecord && readWritePermission){  // 判断是否开启记谱模式，以及是否有读写权限
            saveRegretToLocal();  // 记录悔棋到本地
        }
    }
}