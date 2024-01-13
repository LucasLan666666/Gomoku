// 挣扎函数，在必死的情况下挣扎一下，万一对方比较笨呢
#include "../gomoku.h"

// 挣扎函数，接受棋盘和电脑颜色作为参数，调整下棋策略，返回落子坐标
Coordinate struggle(signed char board[SIZE][SIZE], signed char computer){
    // 优先堵对方的五连（如果对面是白棋，还要堵长连）
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++){
            Coordinate coordinate = {i, j};
            if (board[i][j] == NOBODY && isValid(board, coordinate, computer, NO) == YES) {
                if (    fiveInARow(board, coordinate, -computer) > 0
                    || (computer == BLACK) ? overline(board, coordinate, -computer) > 0 : NO
                    ) {
                    return coordinate;
                }
            }
        }
    }
    // 如果对方没有五连，那么就堵对方三和四比较多的地方
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++){
            Coordinate coordinate = {i, j};
            if (board[i][j] == NOBODY && isValid(board, coordinate, computer, NO) == NO) {
                if (isValid(board, coordinate, -computer, NO) == YES) {
                    if (    straightFour(board, coordinate, -computer) > 0
                        || (three(board, coordinate, -computer) + four(board, coordinate, -computer) > 1)
                        ) {
                        return coordinate;
                    }
                }
            }
        }
    }
    return gorilla();
}