// 此文件用于玩家的落子
#include <ctype.h>
#include "../gomoku.h"

// 将玩家的输入转化为坐标，若为合法坐标，则返回0，否则返回-1
int inputToCoordinate(void) {
    int i = 0; // 用于遍历 line

    // 将当下横纵坐标清零，考虑到存在输入错误的情况
    stepRecord[stepNum].x = 0;
    stepRecord[stepNum].y = 0;

    if (isdigit(line[0])) {  // 读取玩家输入的坐标(先数字后字母)
        while (isdigit(line[i])) {
            stepRecord[stepNum].x = stepRecord[stepNum].x * 10 + line[i] - '0';
            i++;
        }
        if (isalpha(line[i])) {
            stepRecord[stepNum].y = line[i] - (line[i] >= 'a' ? 'a' : 'A');
            i++;
        } else {
            return -1;
        }
    } else if (isalpha(line[0])) {  // 读取玩家输入的坐标(先字母后数字)
        stepRecord[stepNum].y = line[i] - (line[i] >= 'a' ? 'a' : 'A');
        i++;
        if (isdigit(line[i])) {
            while (isdigit(line[i])) {
                stepRecord[stepNum].x = stepRecord[stepNum].x * 10 + line[i] - '0';
                i++;
            }
        } else {
            return -1;
        }
    } else {
        return -1;
    }
    // 由于棋盘规定行数方向和打印方向相反，所以要反转一下
    stepRecord[stepNum].x = SIZE - stepRecord[stepNum].x;

    // 确保没有多余输入
    while (isspace(line[i]))
        i++;
    if (line[i] != '\0')
        return -1;

    // 将心中棋盘转换为虚拟棋盘
    signed char vBoard[SIZE][SIZE];
    initVBoard(vBoard);
    innerBoard2VBoard(vBoard);
    // 判断是否合法坐标
    if (isValid(vBoard, stepRecord[stepNum], player, YES)) {
        return 0;
    } else {
        return -1;
    }
}

// 将玩家当前输入的坐标转化为棋盘上的落子，并更新棋子的状态
void coordinateToPlaceStone(void) {
    // 下面将坐标转化为落子
    // 改变上一步的落子状态，使其不再是当前落子位置（加判断，是因为第一次黑方下棋是没有上一步的）
    if (stepNum > 0) {
        innerBoard[stepRecord[stepNum - 1].x][stepRecord[stepNum - 1].y].current = NO;
    }

    // 改变当前棋子的落子状态
    innerBoard[stepRecord[stepNum].x][stepRecord[stepNum].y].current = YES;
    innerBoard[stepRecord[stepNum].x][stepRecord[stepNum].y].player = player;
}
