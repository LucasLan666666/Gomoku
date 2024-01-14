// 此文件用于对活四的判断
#include "../gomoku.h"

// 判断活四，返回活四的数量
int straightFour(signed char board[SIZE][SIZE], Coordinate coordinate, signed char player) {
    signed char x = coordinate.x;
    signed char y = coordinate.y;
    signed char directions[4][2] = {{1, 0}, {0, 1}, {1, 1}, {1, -1}}; // 四个方向：水平、垂直、主对角线、副对角线
    signed char board_copy[SIZE][SIZE];
    int num = 0;

    copyBoard(board_copy, board); // 再构建一个棋盘副本
    board_copy[x][y] = player; // 假设落子

   // 遍历四个方向
    for (int i = 0; i < 4; i++) {
        int count = 1; // 连子数，包括当前位置
        signed char dx1 =  directions[i][0];
        signed char dy1 =  directions[i][1];
        signed char dx2 = -directions[i][0];
        signed char dy2 = -directions[i][1];

       // 向一个方向查找
        while (x + dx1 >= 0 && x + dx1 < SIZE && y + dy1 >= 0 && y + dy1 < SIZE && board_copy[x + dx1][y + dy1] == player) {
            count++;
            dx1 += directions[i][0];
            dy1 += directions[i][1];
        }

       // 向相反方向查找
        while (x + dx2 >= 0 && x + dx2 < SIZE && y + dy2 >= 0 && y + dy2 < SIZE && board_copy[x + dx2][y + dy2] == player) {
            count++;
            dx2 -= directions[i][0];
            dy2 -= directions[i][1];
        }

       // 四子连珠类型，一对方向上只有一种，但可能在两个方向形成五子连珠
        if (count == 4) {
           // 判断两端是否能落子
            int available = 0; // 记录两端能落子的空位数量
           // 先看正方向一端能否落子
            if (x + dx1 >= 0 && x + dx1 < SIZE && y + dy1 >= 0 && y + dy1 < SIZE && board_copy[x + dx1][y + dy1] == NOBODY) {
                Coordinate newCoordinate = {x + dx1, y + dy1};
               // 多看一格，确保不是长连
                dx1 += directions[i][0];
                dy1 += directions[i][1];
                if (x + dx1 < 0 || x + dx1 >= SIZE || y + dy1 < 0 || y + dy1 >= SIZE || board_copy[x + dx1][y + dy1] != player) {
                    if (isForbiddenMove(board_copy, newCoordinate, player) == NO) { // 判断第五颗棋子能否落下
                        available++;
                    }
                }
               // 撤销多看的一格
                dx1 -= directions[i][0];
                dy1 -= directions[i][1];
            }
           // 再看反方向一端能否落子
            if (x + dx2 >= 0 && x + dx2 < SIZE && y + dy2 >= 0 && y + dy2 < SIZE && board_copy[x + dx2][y + dy2] == NOBODY) {
                Coordinate newCoordinate = {x + dx2, y + dy2};
               // 多看一格，确保不是长连
                dx2 -= directions[i][0];
                dy2 -= directions[i][1];
                if (x + dx2 < 0 || x + dx2 >= SIZE || y + dy2 < 0 || y + dy2 >= SIZE || board_copy[x + dx2][y + dy2] != player) {
                    if (isForbiddenMove(board_copy, newCoordinate, player) == NO) { // 判断第五颗棋子能否落下
                        available++;
                    }
                }
               // 撤销多看的一格
                dx2 += directions[i][0];
                dy2 += directions[i][1];
            }
            if (available == 2) {
                num++;
            }
        }
    }
    return num;
}
