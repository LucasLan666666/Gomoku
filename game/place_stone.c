// 此文件用于玩家的落子
#include <ctype.h>
#include "gomoku.h"

// 将玩家的输入转化为坐标，若为合法坐标，则返回0，否则返回-1
int inputToCoordinate(void){
    int i = 0; // 用于遍历 line

    // 将当下横纵坐标清零，考虑到存在输入错误的情况
    stepRecord[stepNum].x = 0;
    stepRecord[stepNum].y = 0;

    if (isdigit(line[0])){  // 读取玩家输入的坐标(先数字后字母)
        while (isdigit(line[i])){
            stepRecord[stepNum].x = stepRecord[stepNum].x * 10 + line[i] - '0';
            i++;
        }       
        if (isalpha(line[i])){
            stepRecord[stepNum].y = line[i] - (line[i] >= 'a' ? 'a' : 'A');
            i++;
        }else{
            return -1;
        }
    }else if (isalpha(line[0])){  // 读取玩家输入的坐标(先字母后数字)
        stepRecord[stepNum].y = line[i] - (line[i] >= 'a' ? 'a' : 'A');
            i++;
        while (isdigit(line[i])){
            stepRecord[stepNum].x = stepRecord[stepNum].x * 10 + line[i] - '0';
            i++;
        }
    }else{
        return -1;
    }
    // 由于棋盘规定行数方向和打印方向相反，所以要反转一下
    stepRecord[stepNum].x = SIZE - stepRecord[stepNum].x;

    // 确保没有多余输入
    while (isspace(line[i]))
        i++;
    if (line[i] != '\0')
        return -1;

    // 判断是否合法坐标
    if (
           (stepRecord[stepNum].x >= 0) && (stepRecord[stepNum].x <= 14) 
        && (stepRecord[stepNum].y >= 0) && (stepRecord[stepNum].y <= 14) 
        && (arrayForInnerBoardLayout[stepRecord[stepNum].x][stepRecord[stepNum].y].player == NOBODY)
        ){
        return 0;
    }else{
        return -1;
    }
}

// 将玩家当前输入的坐标转化为棋盘上的落子，并更新棋子的状态
void coordinateToPlaceStone(void){
    // 下面将坐标转化为落子
    // 改变上一步的落子状态，使其不再是当前落子位置（加判断，是因为第一次黑方下棋是没有上一步的）
    if (stepNum > 0){
        arrayForInnerBoardLayout[stepRecord[stepNum - 1].x][stepRecord[stepNum - 1].y].current = NO;
    }

    // 改变当前棋子的落子状态
    arrayForInnerBoardLayout[stepRecord[stepNum].x][stepRecord[stepNum].y].current = YES;
    arrayForInnerBoardLayout[stepRecord[stepNum].x][stepRecord[stepNum].y].player = player;

    //该步下完后，更新整个棋盘上目前已经落子的每个棋子的状态
    for (int i = 0; i <= stepNum; i++){
        // 北方的连子数
        for (
            int j = 1;
            (j <= 4)
            && (stepRecord[i].y + j <= 14)
            && (arrayForInnerBoardLayout[stepRecord[i].x][stepRecord[i].y + j].player == arrayForInnerBoardLayout[stepRecord[i].x][stepRecord[i].y].player);
            j++, arrayForInnerBoardLayout[stepRecord[i].x][stepRecord[i].y].direction[0]++
            );
        // 东北方的连子数
        for (
            int j = 1;
            (j <= 4)
            && (stepRecord[i].y + j <= 14) && (stepRecord[i].x + j <= 14)
            && (arrayForInnerBoardLayout[stepRecord[i].x + j][stepRecord[i].y + j].player == arrayForInnerBoardLayout[stepRecord[i].x][stepRecord[i].y].player);
            j++, arrayForInnerBoardLayout[stepRecord[i].x][stepRecord[i].y].direction[1]++
            );
        // 东方的连子数
        for (
            int j = 1;
            (j <= 4)
            && (stepRecord[i].x + j <= 14)
            && (arrayForInnerBoardLayout[stepRecord[i].x + j][stepRecord[i].y].player == arrayForInnerBoardLayout[stepRecord[i].x][stepRecord[i].y].player);
            j++, arrayForInnerBoardLayout[stepRecord[i].x][stepRecord[i].y].direction[2]++
            );
        // 东南方的连子数
        for (
            int j = 1;
            (j <= 4)
            && (stepRecord[i].y - j >= 0) && (stepRecord[i].x + j <= 14)
            && (arrayForInnerBoardLayout[stepRecord[i].x + j][stepRecord[i].y - j].player == arrayForInnerBoardLayout[stepRecord[i].x][stepRecord[i].y].player);
            j++, arrayForInnerBoardLayout[stepRecord[i].x][stepRecord[i].y].direction[3]++
            );
        // 南方的连子数
        for (
            int j = 1;
            (j <= 4)
            && (stepRecord[i].y - j >= 0)
            && (arrayForInnerBoardLayout[stepRecord[i].x][stepRecord[i].y - j].player == arrayForInnerBoardLayout[stepRecord[i].x][stepRecord[i].y].player);
            j++, arrayForInnerBoardLayout[stepRecord[i].x][stepRecord[i].y].direction[4]++
            );
        // 西南方的连子数
        for (
            int j = 1;
            (j <= 4)
            && (stepRecord[i].y - j >= 0) && (stepRecord[i].x - j >= 0)
            && (arrayForInnerBoardLayout[stepRecord[i].x - j][stepRecord[i].y - j].player == arrayForInnerBoardLayout[stepRecord[i].x][stepRecord[i].y].player);
            j++, arrayForInnerBoardLayout[stepRecord[i].x][stepRecord[i].y].direction[5]++
            );
        // 西方的连子数
        for (
            int j = 1;
            (j <= 4)
            && (stepRecord[i].x - j >= 0)
            && (arrayForInnerBoardLayout[stepRecord[i].x - j][stepRecord[i].y].player == arrayForInnerBoardLayout[stepRecord[i].x][stepRecord[i].y].player);
            j++, arrayForInnerBoardLayout[stepRecord[i].x][stepRecord[i].y].direction[6]++
            );
        // 西北方的连子数
        for (
            int j = 1;
            (j <= 4)
            && (stepRecord[i].y + j <= 14) && (stepRecord[i].x - j >= 0)
            && (arrayForInnerBoardLayout[stepRecord[i].x - j][stepRecord[i].y + j].player == arrayForInnerBoardLayout[stepRecord[i].x][stepRecord[i].y].player);
            j++, arrayForInnerBoardLayout[stepRecord[i].x][stepRecord[i].y].direction[7]++
            );
    }
}
