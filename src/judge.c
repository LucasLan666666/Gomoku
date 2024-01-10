// 此文件用于对局势进行分析判断
#include <stdio.h>
#include "gomoku.h"

// 判断是否有胜者出现：若黑棋获胜，返回 BLACK；白棋获胜，返回 WHITE；未出现胜者，返回 NOBODY
int judgeWin(void){
    // 将心中棋盘转换为虚拟棋盘
    int vBoard[SIZE][SIZE];
    initVBoard(vBoard);
    innerBoard2VBoard(vBoard);
    int directions[4][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};  // 横向，纵向，主对角线，副对角线

    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            if (vBoard[i][j] != NOBODY){
                for (int k = 0; k < 4; k++){
                    int count = 0;
                    int x = i;
                    int y = j;
                    while (x >= 0 && x < SIZE && y >= 0 && y < SIZE && vBoard[x][y] == vBoard[i][j]){
                        count++;
                        x += directions[k][0];
                        y += directions[k][1];
                    }
                    if (count >= 5){
                        return vBoard[i][j];
                    }
                }
            }
        }
    }
    return NOBODY;
}

// 判断下棋位置是否合法，合法返回 YES，否则返回 NO
int isValid(struct placeStone coordinate){
    // 将心中棋盘转换为虚拟棋盘
    int vBoard[SIZE][SIZE];
    initVBoard(vBoard);
    innerBoard2VBoard(vBoard);
    if (   vBoard[coordinate.x][coordinate.y] == NOBODY
        && coordinate.x >= 0 && coordinate.x < SIZE
        && coordinate.y >= 0 && coordinate.y < SIZE
        && isForbiddenMove(vBoard, coordinate) == NO){
            return YES;    
    }else{
        if (isForbiddenMove(vBoard, coordinate) == OVERLINE){
            printf("    长连禁手！\n");
        }else if (isForbiddenMove(vBoard, coordinate) == D_THREE){
            printf("    双三禁手！\n");
        }else if (isForbiddenMove(vBoard, coordinate) == D_FOUR){
            printf("    双四禁手！\n");
        }else if (isForbiddenMove(vBoard, coordinate) == COMBINE){
            printf("    组合禁手！\n");
        }
        return NO;
    }
}

// 判断禁手，是返回禁手类型，否返回 NO
int isForbiddenMove(int vBoard[SIZE][SIZE], struct placeStone coordinate){
    if (player == WHITE){
        return NO;
    }if (fiveInARow(vBoard, coordinate) >= 1){
        return NO;
    }else if (overline(vBoard, coordinate) >= 1){
        return OVERLINE;
    }else if (three(vBoard, coordinate) >= 2 && four(vBoard, coordinate) == 0 && straightFour(vBoard, coordinate) == 0){
        return D_THREE;
    }else if ((four(vBoard, coordinate) + straightFour(vBoard, coordinate)) >= 2 && three(vBoard, coordinate) == 0){
        return D_FOUR;
    }else if (three(vBoard, coordinate) >= 2 || (four(vBoard, coordinate) + straightFour(vBoard, coordinate)) >= 2){
        return COMBINE;
    }else{
        return NO;
    }
}
