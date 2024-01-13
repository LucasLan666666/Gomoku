// 本文件用于实现对棋盘的打分
#include "../gomoku.h"

// 打分函数，接受棋盘作为参数，返回一个分数
int evaluate(signed char board[SIZE][SIZE], signed char computer) {
    // 记录分数
    int score = 0;

    if (computer == BLACK) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                Coordinate coordinate = {i, j};
                if (board[i][j] == NOBODY && isValid(board, coordinate, BLACK, NO) == YES) {
                    if (   fiveInARow(board, coordinate, BLACK) > 0
                        || (three(board, coordinate, BLACK) == 1 && (four(board, coordinate, BLACK) + straightFour(board, coordinate, BLACK)) == 1)
                        || straightFour(board, coordinate, BLACK) > 0
                        ) { // 如果黑方能赢，直接返回最大值
                        return 100000000;
                    } else if (four(board, coordinate, BLACK) > 0) {
                        score += 1000;
                    } else if (threeForWin(board, coordinate, BLACK) > 0) {
                        score += 50 * threeForWin(board, coordinate, BLACK);
                    } else if (sleepThree(board, coordinate, BLACK) > 0) {
                        score += 10 * sleepThree(board, coordinate, BLACK);
                    // } else if (two(board, coordinate, BLACK) > 0) {
                    //     score += 1000;
                    }
                } else if (board[i][j] == WHITE) {
                    if (   fiveInARow(board, coordinate, WHITE) > 0
                        || overline(board, coordinate, WHITE) > 0
                        || (three(board, coordinate, WHITE) + four(board, coordinate, WHITE)  > 1)
                        || straightFour(board, coordinate, player)
                        ) { // 如果白方能赢，直接返回最小值
                        return -2000000000;
                    } else if (four(board, coordinate, WHITE) > 0) {
                        score -= 1000;
                    } else if (threeForWin(board, coordinate, WHITE) > 0) {
                        score -= 100 * threeForWin(board, coordinate, WHITE);
                    } else if (sleepThree(board, coordinate, WHITE) > 0) {
                        score -= 15 * sleepThree(board, coordinate, WHITE);
                    // } else if (two(board, coordinate, WHITE) > 0) {
                    //     score -= 1000;
                    }
                }
            }
        }
    } else {
        for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                Coordinate coordinate = {i, j};
                if (board[i][j] == NOBODY && isValid(board, coordinate, WHITE, NO) == YES) {
                    if (    three(board, coordinate, WHITE) + four(board, coordinate, WHITE) > 1
                        ||  straightFour(board, coordinate, WHITE) > 0
                        ) { // 如果白方能赢，直接返回最大值
                        return 0;
                    } else if (four(board, coordinate, WHITE) > 0) {
                        score += 0;
                    } else if (threeForWin(board, coordinate, WHITE) > 0) {
                        score += 0 * threeForWin(board, coordinate, WHITE);
                    } else if (sleepThree(board, coordinate, WHITE) > 0) {
                        score += 0 * sleepThree(board, coordinate, WHITE);
                    // } else if (two(board, coordinate, WHITE) > 0) {
                    //     score += 1000;
                    }
                } else if (board[i][j] == BLACK) {
                    if (   fiveInARow(board, coordinate, BLACK) > 0
                        || (three(board, coordinate, BLACK) == 1 && (four(board, coordinate, BLACK) + straightFour(board, coordinate, BLACK)) == 1)
                        || straightFour(board, coordinate, BLACK) > 0) { // 如果黑方能赢，直接返回最小值
                        return -2000000000;
                    } else if (four(board, coordinate, BLACK) > 0) {
                        score -= 1000000;
                    } else if (threeForWin(board, coordinate, BLACK) > 0) {
                        score -= 100000 * threeForWin(board, coordinate, BLACK);
                    } else if (sleepThree(board, coordinate, BLACK) > 0) {
                        score -= 5000 * sleepThree(board, coordinate, BLACK);
                    // } else if (two(board, coordinate, BLACK) > 0) {
                    //     score -= 1000;
                    }
                }
            }
        }
    }
    return score;
}