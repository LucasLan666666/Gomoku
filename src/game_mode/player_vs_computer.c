// 本文件包含人机对战相关内容
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "../gomoku.h"

void playerVsComputer(void) {
    int quit = NO; // 表示是否退出
    int check; // 储存读取输入的相关信息
    int regret = NO; // 初始化悔棋为否
    player = BLACK;  //黑方先落子，所以初始化 player 为 BLACK
    stepNum = 0; // 初始化步数为 0
    initInnerBoard(); // 初始化一个空棋盘

    while (quit == NO) {
        innerBoard2Displayboard(); // 将心中的棋盘转成用于显示的棋盘
        printDisplayBoard(); // 显示棋盘
        if (stepNum == 0 && regret == YES) {
            printf("    已经是第一步，无法再继续悔棋了！\n");
        } else if (stepNum > 0 && regret == YES) {
            printf("    悔棋成功！\n");
        }
        regret = NO;

        if (stepNum > 0 && player != computer) {
            sprintf(stepName, "%c%d", stepRecord[stepNum - 1].y + 'A', SIZE - stepRecord[stepNum - 1].x); // 刷新 stepName
            printf("    电脑落子的位置为：%s\n", stepName);
        }

        // 眠三函数功能测试
        // testForSleepThree(stepRecord[stepNum - 2]);

        // 输出当前等待落子的玩家
        if (player != computer) {
            printf("    现在请%s落子：", (player == BLACK) ? "黑方" : "白方");
        }

        if (player != computer) {
            mygetline(line); // 从键盘读取输入到 line 中
           // 对玩家输入进行判断：如果输入的是坐标，返回 0；如果输入的是 quit 指令，返回 1；如果输入的是 regret 指令，返回 2；如果输入有误，返回 -1
            while ((check = inputCheckInGame()) == -1) {
                printf("    您的输入有误，请重新输入：");
                mygetline(line);
            }
        } else {
            stepRecord[stepNum] = AI(computer); // AI 下棋
            // stepRecord[stepNum] = testAI(); // 测试AI 下棋
            // stepRecord[stepNum] = gorilla(); // 电脑随机下棋
            // stepRecord[stepNum] = testSpeed(); // 测试电脑运算速度
            check = 0; // 因为电脑默认只会下棋，不会悔棋
        }
        switch (check) {
        case 0:
            quit = placeStonePvE(); break;
        case 1:
            quit = YES; break; // 退出 while 循环
        case 2:
            regretPvE(); regret = YES; break;
        default:
            break;
        }
    }
}

// 人机对战下棋的主要内容，将玩家输入的正确坐标转化为心中的棋盘，记录棋谱，并判赢；如果是电脑，直接修改 innerBoard 的内容；若判得游戏结束，返回 YES
int placeStonePvE(void) {
    int check; // 储存读取输入的相关信息
    coordinateToPlaceStone(); // 将坐标转化为棋盘上的落子
    if (gameRecord && readWritePermission) { // 判断是否开启记谱模式，以及是否有读写权限
        recordGameRoundToLocal(); // 记录棋谱到本地
    }

    // 将心中棋盘转换为虚拟棋盘
    signed char vBoard[SIZE][SIZE];
    initVBoard(vBoard);
    innerBoard2VBoard(vBoard);

    if (getWinner(vBoard) != NOBODY || stepNum == MAXSTEP - 1) { // 判断是否有玩家获胜或者平局
        innerBoard2Displayboard();
        printDisplayBoard(); // 显示棋盘
        if (getWinner(vBoard) != NOBODY) {
            printf("    恭喜%s获胜！\n", (player == BLACK) ? "黑方" : "白方");
        } else {
            printf("    平局！\n");
        }
        printf("    输入 q 返回主页, 或者输入 r 悔棋：");
        mygetline(line);
        // 对玩家输入进行判断：如果输入的是坐标，返回 0；如果输入的是 quit 指令，返回 1；如果输入的是 regret 指令，返回 2；如果输入有误，返回 -1
        while ((check = inputCheckInGame()) == -1 || check == 0) {
            printf("    您的输入有误，请重新输入:");
            mygetline(line);
        }
        if (check == 1) {
            return YES;
        } else {
            if (player == computer) {
                stepNum++;
                player = -player;
            } else {
                stepNum += 2;
            }
            regretPvE();
            return NO;
        }
    }
    // 步数+1
    stepNum++;
    // 转换玩家，黑方下完白方下，白方下完黑方下
    player = -player;

    return NO;
}

// 人机对战模式的悔棋模式
void regretPvE(void) {
    // 这里只有人会悔棋，考虑到人会在机器下完后悔棋，所以一次会悔两步（到上一次自己下棋的地方）
    regretPvP();
    regretPvP();
}
