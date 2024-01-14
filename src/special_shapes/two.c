// 此文件用于对二的判断，后来发现运算时间太长，所以放弃了
#include "../gomoku.h"

// 判断二，返回二的数量
int two(signed char board[SIZE][SIZE], Coordinate coordinate, signed char player) {
    signed char x = coordinate.x;
    signed char y = coordinate.y;
    signed char directions[4][2] = {{1, 0}, {0, 1}, {1, 1}, {1, -1}}; // 四个方向：水平、垂直、主对角线、副对角线
    signed char board_copy[SIZE][SIZE];
    int num = 0;

    copyBoard(board_copy, board); // 再构建一个棋盘副本
    board_copy[x][y] = player; // 假设落子

   // 遍历四个方向
    for (int i = 0; i < 4; i++) {
        signed char dx1 =  directions[i][0];
        signed char dy1 =  directions[i][1];
        signed char dx2 = -directions[i][0];
        signed char dy2 = -directions[i][1];

       // 正方向
        if (x + 4*dx1 >= 0 && x + 4*dx1 < SIZE && y + 4*dy1 >= 0 && y + 4*dy1 < SIZE) { // 判断从此处出发是否塞得下一个五子连珠
            if (   (x + 5*dx1 < 0 || x + 5*dx1 >= SIZE || y + 5*dy1 < 0 || y + 5*dy1 >= SIZE || board_copy[x + 5*dx1][y + 5*dy1] != player)
                && (x + dx2 < 0 || x + dx2 >= SIZE || y + dy2 < 0 || y + dy2 >= SIZE || board_copy[x + dx2][y + dy2] != player)){ // 排除长连
                Coordinate newCoordinate1 = {x + dx1, y + dy1};
                Coordinate newCoordinate2 = {x + 2*dx1, y + 2*dy1};
                Coordinate newCoordinate3 = {x + 3*dx1, y + 3*dy1};
                Coordinate newCoordinate4 = {x + 4*dx1, y + 4*dy1};
                if (
                    (  board_copy[x +   dx1][y +   dy1] == player
                    && board_copy[x + 2*dx1][y + 2*dy1] == NOBODY && isForbiddenMove(board_copy, newCoordinate2, player) == NO 
                    && board_copy[x + 3*dx1][y + 3*dy1] == NOBODY && isForbiddenMove(board_copy, newCoordinate3, player) == NO
                    && board_copy[x + 4*dx1][y + 4*dy1] == NOBODY && isForbiddenMove(board_copy, newCoordinate4, player) == NO)
                ||  (  board_copy[x +   dx1][y +   dy1] == NOBODY && isForbiddenMove(board_copy, newCoordinate1, player) == NO
                    && board_copy[x + 2*dx1][y + 2*dy1] == player
                    && board_copy[x + 3*dx1][y + 3*dy1] == NOBODY && isForbiddenMove(board_copy, newCoordinate3, player) == NO
                    && board_copy[x + 4*dx1][y + 4*dy1] == NOBODY && isForbiddenMove(board_copy, newCoordinate4, player) == NO)
                ||  (  board_copy[x +   dx1][y +   dy1] == NOBODY && isForbiddenMove(board_copy, newCoordinate1, player) == NO
                    && board_copy[x + 2*dx1][y + 2*dy1] == NOBODY && isForbiddenMove(board_copy, newCoordinate2, player) == NO
                    && board_copy[x + 3*dx1][y + 3*dy1] == player
                    && board_copy[x + 4*dx1][y + 4*dy1] == NOBODY && isForbiddenMove(board_copy, newCoordinate4, player) == NO)
                ||  (  board_copy[x +   dx1][y +   dy1] == NOBODY && isForbiddenMove(board_copy, newCoordinate1, player) == NO
                    && board_copy[x + 2*dx1][y + 2*dy1] == NOBODY && isForbiddenMove(board_copy, newCoordinate2, player) == NO
                    && board_copy[x + 3*dx1][y + 3*dy1] == NOBODY && isForbiddenMove(board_copy, newCoordinate3, player) == NO
                    && board_copy[x + 4*dx1][y + 4*dy1] == player)
                ) {
                    num++;
                }
            }
        }
       // 反方向
    }
    return num;
}
