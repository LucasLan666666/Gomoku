// 此文件用于对活四的判断
#include "gomoku.h"

// 判断活四，返回活四的数量
int straightFour(int board[SIZE][SIZE], struct placeStone coordinate, int player){
    int x = coordinate.x;
    int y = coordinate.y;
    int directions[4][2] = {{1, 0}, {0, 1}, {1, 1}, {1, -1}}; // 四个方向：水平、垂直、主对角线、副对角线
    int board_copy[SIZE][SIZE];
    int num = 0;

    copyBoard(board_copy, board); // 再构建一个棋盘副本
    board_copy[x][y] = player;  // 假设落子

    // 遍历四个方向
    for (int i = 0; i < 4; i++){
        int count = 1;  // 连子数，包括当前位置
        int dx1 =  directions[i][0];
        int dy1 =  directions[i][1];
        int dx2 = -directions[i][0];
        int dy2 = -directions[i][1];

        // 向一个方向查找
        while (x + dx1 >= 0 && x + dx1 < SIZE && y + dy1 >= 0 && y + dy1 < SIZE && board_copy[x + dx1][y + dy1] == player){
            count++;
            dx1 += directions[i][0];
            dy1 += directions[i][1];
        }

        // 向相反方向查找
        while (x + dx2 >= 0 && x + dx2 < SIZE && y + dy2 >= 0 && y + dy2 < SIZE && board_copy[x + dx2][y + dy2] == player){
            count++;
            dx2 -= directions[i][0];
            dy2 -= directions[i][1];
        }

        // 四子连珠类型，一对方向上只有一种，但可能在两个方向形成五子连珠
        if (count == 4){
            // 判断两端是否能落子
            int available = 0; // 记录两端能落子的空位数量
            // 先看正方向一端能否落子
            if (x + dx1 >= 0 && x + dx1 < SIZE && y + dy1 >= 0 && y + dy1 < SIZE && board_copy[x + dx1][y + dy1] == NOBODY){
                struct placeStone newCoordinate = {x + dx1, y + dy1};
                if (isForbiddenMove(board_copy, newCoordinate, player) == NO){ // 判断第五颗棋子能否落下
                    available++;
                }
            }
            // 再看反方向一端能否落子
            if (x + dx2 >= 0 && x + dx2 < SIZE && y + dy2 >= 0 && y + dy2 < SIZE && board_copy[x + dx2][y + dy2] == NOBODY){
                struct placeStone newCoordinate = {x + dx2, y + dy2};
                if (isForbiddenMove(board_copy, newCoordinate, player) == NO){ // 判断第五颗棋子能否落下
                    available++;
                }
            }
            if (available == 2){
                num++;
            }
        }
    }
    return num;
}
