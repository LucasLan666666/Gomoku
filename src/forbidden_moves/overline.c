// 此文件用于对长连的判断
#include "../gomoku.h"

// 判断长连，返回长连的数量
int overline(int board[SIZE][SIZE], Coordinate coordinate, int player){
    int x = coordinate.x;
    int y = coordinate.y;
    int dx;
    int dy;
    int directions[4][2] = {{1, 0}, {0, 1}, {1, 1}, {1, -1}}; // 四个方向：水平、垂直、主对角线、副对角线
    int board_copy[SIZE][SIZE];
    int num = 0;

    copyBoard(board_copy, board); // 再构建一个棋盘副本

    // 遍历四个方向
    for (int i = 0; i < 4; i++) {
        int count = 1;  // 连子数，包括当前位置

        // 向一个方向查找
        dx = directions[i][0];
        dy = directions[i][1];
        while (x + dx >= 0 && x + dx < SIZE && y + dy >= 0 && y + dy < SIZE && board_copy[x + dx][y + dy] == player){
            count++;
            dx += directions[i][0];
            dy += directions[i][1];
        }

        // 向相反方向查找
        dx = -directions[i][0];
        dy = -directions[i][1];
        while (x + dx >= 0 && x + dx < SIZE && y + dy >= 0 && y + dy < SIZE && board_copy[x + dx][y + dy] == player){
            count++;
            dx -= directions[i][0];
            dy -= directions[i][1];
        }

        // 判断连子数
        if (count > 5){
            num++;
        }
    }
    return num;
}
