// 此文件用于对长连的判断
#include "../gomoku.h"

// 判断长连，返回长连的数量
int overline(signed char board[SIZE][SIZE], Coordinate coordinate, signed char player) {
    signed char x = coordinate.x;
    signed char y = coordinate.y;
    signed char dx;
    signed char dy;
    int num = 0;

    // 遍历四个方向
    for (int i = 0; i < 4; i++) {
        int count = 1; // 连子数，包括当前位置

        // 向一个方向查找
        dx = directions[i][0];
        dy = directions[i][1];
        while (x + dx >= 0 && x + dx < SIZE && y + dy >= 0 && y + dy < SIZE && board[x + dx][y + dy] == player) {
            count++;
            dx += directions[i][0];
            dy += directions[i][1];
        }

        // 向相反方向查找
        dx = -directions[i][0];
        dy = -directions[i][1];
        while (x + dx >= 0 && x + dx < SIZE && y + dy >= 0 && y + dy < SIZE && board[x + dx][y + dy] == player) {
            count++;
            dx -= directions[i][0];
            dy -= directions[i][1];
        }

        // 判断连子数
        if (count > 5) {
            num++;
        }
    }
    return num;
}
