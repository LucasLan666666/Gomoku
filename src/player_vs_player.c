// 本文件包含双人对战相关内容
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "gomoku.h"

int regret;  // 记录是否悔棋，YES 为是，NO 为否

void playerVsPlayer(void){
    int quit = NO;  // 表示是否退出
    int check;  // 储存读取输入的相关信息
    regret = NO;  // 初始化悔棋为否
    player = BLACK;  //黑方先落子，所以初始化 player 为 1
    stepNum = 0;  // 初始化步数为 0
    initInnerBoard(); // 初始化一个空棋盘

    while (quit == NO){
        innerBoard2Displayboard();  // 将心中的棋盘转成用于显示的棋盘
        printDisplayBoard();  // 显示棋盘

        if (stepNum == 0 && regret == YES){
            printf("    已经是第一步，无法再悔棋了！\n");
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
            quit = pvp_placeStone();
            break;
        case 1:
            quit = YES; break;  // 退出 while 循环
        case 2:
            regret1(); regret = YES; break;
        default:
            break;
        }
    }
}

// 人人对战下棋的主要内容，将玩家输入的正确坐标转化为心中的棋盘，记录棋谱，并判赢；若判得游戏结束，返回 YES
int pvp_placeStone(void){
    int check;  // 储存读取输入的相关信息
    coordinateToPlaceStone();  // 将坐标转化为棋盘上的落子
    if (gameRecord && readWritePermission){  // 判断是否开启记谱模式，以及是否有读写权限
        recordGameRoundToLocal();  // 记录棋谱到本地
    }
    if (judgeWin() != NOBODY){  // 判断是否有玩家获胜
        innerBoard2Displayboard();
        printDisplayBoard();  // 显示棋盘
        printf("    恭喜%s获胜！\n", (player == BLACK) ? "黑方" : "白方");
        printf("    输入 q 返回主页, 或者输入 r 悔棋\n");
        mygetline();
        // 对玩家输入进行判断：如果输入的是坐标，返回 0；如果输入的是 quit 指令，返回 1；如果输入的是 regret 指令，返回 2；如果输入有误，返回 -1
        while ((check = inputCheckInGame()) == -1 || check == 0){
            printf("    你的输入有误，请重新输入：\n\t");
            mygetline();
        }
        if (check == 1){
            return YES;
        }else{
            stepNum++;
            changePlayer();
            regret1();
            return NO;
        }
    }
    // 步数+1
    stepNum++;
    // 转换玩家，黑方下完白方下，白方下完黑方下
    changePlayer();

    return NO;
}

// 人人对战模式的悔棋模式
void regret1(void){
    if (stepNum != 0){
        // 步数-1
        stepNum--;
        // 将上一步落子清除
        innerBoard[stepRecord[stepNum].x][stepRecord[stepNum].y].current = NO;
        innerBoard[stepRecord[stepNum].x][stepRecord[stepNum].y].player = NOBODY;
        for (int k = 0; k < 8; k++){
            innerBoard[stepRecord[stepNum].x][stepRecord[stepNum].y].direction[k] = 0;
        }
        // 转换为上一个玩家
        changePlayer();
        if (gameRecord && readWritePermission){  // 判断是否开启记谱模式，以及是否有读写权限
            saveRegretToLocal();  // 记录悔棋到本地
        }
    }
}