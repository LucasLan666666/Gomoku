// 挣扎函数，在必死的情况下挣扎一下，万一对方比较笨呢
#include "../gomoku.h"

// 挣扎函数，接受棋盘和电脑颜色作为参数，调整下棋策略，返回落子坐标
Coordinate struggle(signed char board[SIZE][SIZE], signed char computer){
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++){
            Coordinate coordinate = {i, j};
            if (board[i][j] == NOBODY && isValid(board, coordinate, computer, NO) == YES) {
                if (    fiveInARow(board, coordinate, -computer) > 0
                    ||  straightFour(board, coordinate, -computer) > 0
                    ) {
                    return coordinate;
                }
            }
        }
    }
    return gorilla();
}