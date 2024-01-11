// 此文件用于对局势进行分析判断
#include <stdio.h>
#include "../gomoku.h"

// 判断是否有胜者出现：若黑棋获胜，返回 BLACK；白棋获胜，返回 WHITE；未出现胜者，返回 NOBODY
int judgeWin(void) {
    // 将心中棋盘转换为虚拟棋盘
    signed char vBoard[SIZE][SIZE];
    initVBoard(vBoard);
    innerBoard2VBoard(vBoard);
    signed char directions[4][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};  // 横向，纵向，主对角线，副对角线

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (vBoard[i][j] != NOBODY) {
                for (int k = 0; k < 4; k++) {
                    int count = 0;
                    signed char x = i;
                    signed char y = j;
                    while (x >= 0 && x < SIZE && y >= 0 && y < SIZE && vBoard[x][y] == vBoard[i][j]) {
                        count++;
                        x += directions[k][0];
                        y += directions[k][1];
                    }
                    if (count >= 5) {
                        return vBoard[i][j];
                    }
                }
            }
        }
    }
    return NOBODY;
}

// 判断下棋位置是否合法，合法返回 YES，否则返回 NO
int isValid(signed char board[SIZE][SIZE], Coordinate coordinate, signed char player, signed char warning) {
    if (   coordinate.x >= 0 && coordinate.x < SIZE
        && coordinate.y >= 0 && coordinate.y < SIZE
        && board[coordinate.x][coordinate.y] == NOBODY
        && isForbiddenMove(board, coordinate, player) == NO) {
        return YES;
    } else {
        if (warning == YES) { // 是否输出错误信息
            if (coordinate.x < 0 || coordinate.x >= SIZE || coordinate.y < 0 || coordinate.y >= SIZE) {
                printf("    超出棋盘范围！\n");
            } else if (board[coordinate.x][coordinate.y] != NOBODY) {
                printf("    此处已有棋子！\n");
            }
            switch (isForbiddenMove(board, coordinate, player)) {
                case OVERLINE:
                    printf("    长连禁手！\n");
                    break;
                case D_THREE:
                    printf("    双三禁手！\n");
                    break;
                case D_FOUR:
                    printf("    双四禁手！\n");
                    break;
                case COMBINE:
                    printf("    组合禁手！\n");
                    break;
            }
        }
        return NO;
    }
}

// 判断禁手，是返回禁手类型，否返回 NO
int isForbiddenMove(signed char vBoard[SIZE][SIZE], Coordinate coordinate, signed char player) {
    if (player == WHITE) {
        return NO;
    }if (fiveInARow(vBoard, coordinate, player) >= 1) {
        return NO;
    } else if (overline(vBoard, coordinate, player) >= 1) {
        return OVERLINE;
    } else if (three(vBoard, coordinate, player) >= 2 && four(vBoard, coordinate, player) == 0 && straightFour(vBoard, coordinate, player) == 0) {
        return D_THREE;
    } else if ((four(vBoard, coordinate, player) + straightFour(vBoard, coordinate, player)) >= 2 && three(vBoard, coordinate, player) == 0) {
        return D_FOUR;
    } else if (three(vBoard, coordinate, player) >= 2 || (four(vBoard, coordinate, player) + straightFour(vBoard, coordinate, player)) >= 2) {
        return COMBINE;
    } else {
        return NO;
    }
}
