// 挣扎函数，我觉得我可以再抢救一下，拒绝摆烂好吧
#include "../gomoku.h"

// 挣扎函数，接受棋盘和电脑颜色作为参数，调整下棋策略，返回落子坐标
Coordinate struggle(signed char board[SIZE][SIZE], signed char computer){
    // 优先堵对方的五连（如果对面是白棋，还要堵长连）
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++){
            Coordinate coordinate = {i, j};
            if (board[i][j] == NOBODY && isValid(board, coordinate, computer, NO) == YES) {
                if (    (fiveInARow(board, coordinate, -computer) > 0)
                    || ((computer == BLACK) ? overline(board, coordinate, WHITE) > 0 : NO)
                    ) {
                    return coordinate;
                }
            }
        }
    }
    // 如果对方没有五连，那么就堵对方其他赢棋点（能形成较多三和四的地方）
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++){
            Coordinate coordinate = {i, j};
            if (board[i][j] == NOBODY && isValid(board, coordinate, computer, NO) == YES) {
                if (isValid(board, coordinate, -computer, NO) == YES) {
                    if (   three(board, coordinate, -computer) + four(board, coordinate, -computer) + straightFour(board, coordinate, -computer) > 1) {
                        return coordinate;
                    }
                }
            }
        }
    }
    // 如果对方没有赢棋点，那么就堵对方冲四和活四
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++){
            Coordinate coordinate = {i, j};
            if (board[i][j] == NOBODY && isValid(board, coordinate, computer, NO) == YES) {
                if (isValid(board, coordinate, -computer, NO) == YES) {
                    if (   straightFour(board, coordinate, -computer) > 0 || four(board, coordinate, -computer) > 0) {
                        return coordinate;
                    }
                }
            }
        }
    }
    // 如果对方没有冲四和活四，那么就堵对方活三
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++){
            Coordinate coordinate = {i, j};
            if (board[i][j] == NOBODY && isValid(board, coordinate, computer, NO) == YES) {
                if (isValid(board, coordinate, -computer, NO) == YES) {
                    if (three(board, coordinate, -computer) > 0) {
                        return coordinate;
                    }
                }
            }
        }
    }
    // 万一有没考虑到的情况就随机落子吧
    return gorilla();
}