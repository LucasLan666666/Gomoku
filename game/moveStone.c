// 此文件用于玩家的落子
#include <ctype.h>
#include "gobang.h"

// 上一步玩家落子的坐标
struct moveStone lastPlayerMoveStone;
// 当前玩家落子的坐标
struct moveStone currentPlayerMoveStone;

// 将玩家的输入转化为坐标，若为合法坐标，则返回0，否则返回-1
int inputToCoordinate(void){
    int i = 0; // 用于遍历line

    // 将当下横纵坐标清零
    currentPlayerMoveStone.x = 0;
    currentPlayerMoveStone.y = 0;

    if (isdigit(line[0])){  // 读取玩家输入的坐标(先数字后字母)
        while (isdigit(line[i])){
            currentPlayerMoveStone.x = currentPlayerMoveStone.x * 10 + line[i] - '0';
            i++;
        }       
        if (isalpha(line[i])){
            currentPlayerMoveStone.y = line[i] - (line[i] >= 'a' ? 'a' : 'A');
            i++;
        }else{
            return -1;
        }
    }else if (isalpha(line[0])){  // 读取玩家输入的坐标(先字母后数字)
        currentPlayerMoveStone.y = line[i] - (line[i] >= 'a' ? 'a' : 'A');
            i++;
        while (isdigit(line[i])){
            currentPlayerMoveStone.x = currentPlayerMoveStone.x * 10 + line[i] - '0';
            i++;
        }
    }else{
        return -1;
    }
    // 由于棋盘规定行数方向和打印方向相反，所以要反转一下
    currentPlayerMoveStone.x = 15 - currentPlayerMoveStone.x;

    // 确保没有多余输入
    if (line[i] != '\0')
        return -1;

    // 判断是否合法坐标
    if (
           (currentPlayerMoveStone.x >= 0) && (currentPlayerMoveStone.x <= 14) 
        && (currentPlayerMoveStone.y >= 0) && (currentPlayerMoveStone.y <= 14) 
        && (arrayForInnerBoardLayout[currentPlayerMoveStone.x][currentPlayerMoveStone.y] == 0)
        ){
        return 0;
    }else{
        return -1;
    }
}

// 将玩家当前输入的坐标转化为棋盘上的落子
void coordinateToMoveStone(void)
{
    // 下面将坐标转化为落子
    if (player == 1){ // 当前玩家为黑方，将棋子放在棋盘上
        // 改变上一步白方的落子状态，使其不再是当前落子位置（加判断，是因为第一次黑方下棋是没有上一步的）
        if (arrayForInnerBoardLayout[lastPlayerMoveStone.x][lastPlayerMoveStone.y] == -2){
            arrayForInnerBoardLayout[lastPlayerMoveStone.x][lastPlayerMoveStone.y] = 2;
        }

        // 改变当前棋子的落子状态
        arrayForInnerBoardLayout[currentPlayerMoveStone.x][currentPlayerMoveStone.y] = -1;
        // 将当前玩家落子坐标赋值给上一步玩家落子坐标，主要是为了区分符号显示
        lastPlayerMoveStone.x = currentPlayerMoveStone.x;
        lastPlayerMoveStone.y = currentPlayerMoveStone.y;

        // 转换玩家，黑方下完白方下
        player = 2;
    }else{
        // 同上
        arrayForInnerBoardLayout[lastPlayerMoveStone.x][lastPlayerMoveStone.y] = 1;
        arrayForInnerBoardLayout[currentPlayerMoveStone.x][currentPlayerMoveStone.y] = -2;
        lastPlayerMoveStone.x = currentPlayerMoveStone.x;
        lastPlayerMoveStone.y = currentPlayerMoveStone.y;
        player = 1;
    }
}