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

// 判断五连，返回五连的数量
int fiveInARow(int board[SIZE][SIZE], struct placeStone coordinate){
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
        while (x + dx >= 0 && x + dx < SIZE && y + dy >= 0 && y + dy < SIZE && board_copy[x + dx][y + dy] == BLACK){
            count++;
            dx += directions[i][0];
            dy += directions[i][1];
        }

        // 向相反方向查找
        dx = -directions[i][0];
        dy = -directions[i][1];
        while (x + dx >= 0 && x + dx < SIZE && y + dy >= 0 && y + dy < SIZE && board_copy[x + dx][y + dy] == BLACK){
            count++;
            dx -= directions[i][0];
            dy -= directions[i][1];
        }

        // 判断连子数
        if (count == 5){
            num++;
        }
    }
    return num;
}

// 判断长连，返回长连的数量
int overline(int board[SIZE][SIZE], struct placeStone coordinate){
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
        while (x + dx >= 0 && x + dx < SIZE && y + dy >= 0 && y + dy < SIZE && board_copy[x + dx][y + dy] == BLACK){
            count++;
            dx += directions[i][0];
            dy += directions[i][1];
        }

        // 向相反方向查找
        dx = -directions[i][0];
        dy = -directions[i][1];
        while (x + dx >= 0 && x + dx < SIZE && y + dy >= 0 && y + dy < SIZE && board_copy[x + dx][y + dy] == BLACK){
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

// 判断冲四，返回冲四的数量
int four(int board[SIZE][SIZE], struct placeStone coordinate){
    int x = coordinate.x;
    int y = coordinate.y;
    int directions[4][2] = {{1, 0}, {0, 1}, {1, 1}, {1, -1}}; // 四个方向：水平、垂直、主对角线、副对角线
    int board_copy[SIZE][SIZE];
    int num = 0;

    copyBoard(board_copy, board); // 再构建一个棋盘副本
    board_copy[x][y] = BLACK;  // 假设落子

    // 遍历四个方向
    for (int i = 0; i < 4; i++){
        int count = 1;  // 连子数，包括当前位置
        int dx1 =  directions[i][0];
        int dy1 =  directions[i][1];
        int dx2 = -directions[i][0];
        int dy2 = -directions[i][1];

        // 向一个方向查找
        while (x + dx1 >= 0 && x + dx1 < SIZE && y + dy1 >= 0 && y + dy1 < SIZE && board_copy[x + dx1][y + dy1] == BLACK){
            count++;
            dx1 += directions[i][0];
            dy1 += directions[i][1];
        }

        // 向相反方向查找
        while (x + dx2 >= 0 && x + dx2 < SIZE && y + dy2 >= 0 && y + dy2 < SIZE && board_copy[x + dx2][y + dy2] == BLACK){
            count++;
            dx2 -= directions[i][0];
            dy2 -= directions[i][1];
        }

        // 四子连珠类型，一对方向上只有一种，但可能在两个方向形成五子连珠
        if (count == 4){
            // 判断两端是否能落子
            int available = 0; // 记录两端能落子的空位数量
            // 先看正方向一端能否落子
            if (x + dx1 >= 0 && x + dx1 < SIZE && y + dy1 >= 0 && y + dy1 < SIZE && board_copy[x + dx1][y + dy1] == NOBODY){
                struct placeStone newCoordinate = {x + dx1, y + dy1};
                if (isForbiddenMove(board_copy, newCoordinate) == NO){ // 判断第五颗棋子能否落下
                    available++;
                }
            }
            // 再看反方向一端能否落子
            if (x + dx2 >= 0 && x + dx2 < SIZE && y + dy2 >= 0 && y + dy2 < SIZE && board_copy[x + dx2][y + dy2] == NOBODY){
                struct placeStone newCoordinate = {x + dx2, y + dy2};
                if (isForbiddenMove(board_copy, newCoordinate) == NO){ // 判断第五颗棋子能否落下
                    available++;
                }
            }
            if (available == 1){
                num++;
            }
        // 1-0-3 类型，可能在两个相反方向上形成不同的冲四，每个冲四只可能有一种成五方式
        }else if (count == 1){
            // 正方向的 1-0-3
            if (x + dx1 >= 0 && x + dx1 < SIZE && y + dy1 >= 0 && y + dy1 < SIZE && board_copy[x + dx1][y + dy1] == NOBODY){ // 判断是不是空位
                int dx_1 = dx1;
                int dy_1 = dy1;
                int count2 = 0;
                struct placeStone newCoordinate = {x + dx1, y + dy1};
                // 跳过空位数三子连珠
                dx_1 += directions[i][0];
                dy_1 += directions[i][1];
                while (x + dx_1 >= 0 && x + dx_1 < SIZE && y + dy_1 >= 0 && y + dy_1 < SIZE && board_copy[x + dx_1][y + dy_1] == BLACK){
                    count2++;
                    dx_1 += directions[i][0];
                    dy_1 += directions[i][1];
                }
                if (count2 == 3){
                    if (isForbiddenMove(board_copy, newCoordinate) == NO){
                        num++;
                    }
                }
            }
            // 反方向的 1-0-3
            if (x + dx2 >= 0 && x + dx2 < SIZE && y + dy2 >= 0 && y + dy2 < SIZE && board_copy[x + dx2][y + dy2] == NOBODY){ // 判断是不是空位
                int dx_2 = dx2;
                int dy_2 = dy2;
                int count2 = 0;
                struct placeStone newCoordinate = {x + dx2, y + dy2};
                // 跳过空位数三子连珠
                dx_2 -= directions[i][0];
                dy_2 -= directions[i][1];
                while (x + dx_2 >= 0 && x + dx_2 < SIZE && y + dy_2 >= 0 && y + dy_2 < SIZE && board_copy[x + dx_2][y + dy_2] == BLACK){
                    count2++;
                    dx_2 -= directions[i][0];
                    dy_2 -= directions[i][1];
                }
                if (count2 == 3){
                    if (isForbiddenMove(board_copy, newCoordinate) == NO){
                        num++;
                    }
                }
            }
        // 3-0-1 类型，可能在两个相反方向上形成不同的冲四，每个冲四只可能有一种成五方式
        }else if (count == 3){
            // 正方向的 3-0-1
            if (x + dx1 >= 0 && x + dx1 < SIZE && y + dy1 >= 0 && y + dy1 < SIZE && board_copy[x + dx1][y + dy1] == NOBODY){
                int dx_1 = dx1;
                int dy_1 = dy1;
                int count2 = 0;
                struct placeStone newCoordinate = {x + dx_1, y + dy_1};
                dx_1 += directions[i][0];
                dy_1 += directions[i][1];
                while (x + dx_1 >= 0 && x + dx_1 < SIZE && y + dy_1 >= 0 && y + dy_1 < SIZE && board_copy[x + dx_1][y + dy_1] == BLACK){
                    count2++;
                    dx_1 += directions[i][0];
                    dy_1 += directions[i][1];
                }
                if (count2 == 1){
                    if (isForbiddenMove(board_copy, newCoordinate) == NO){
                        num++;
                    }
                }
            }
            // 反方向的 3-0-1
            if (x + dx2 >= 0 && x + dx2 < SIZE && y + dy2 >= 0 && y + dy2 < SIZE && board_copy[x + dx2][y + dy2] == NOBODY){
                int dx_2 = dx2;
                int dy_2 = dy2;
                int count2 = 0;
                struct placeStone newCoordinate = {x + dx_2, y + dy_2};
                dx_2 -= directions[i][0];
                dy_2 -= directions[i][1];
                while (x + dx_2 >= 0 && x + dx_2 < SIZE && y + dy_2 >= 0 && y + dy_2 < SIZE && board_copy[x + dx_2][y + dy_2] == BLACK){
                    count2++;
                    dx_2 -= directions[i][0];
                    dy_2 -= directions[i][1];
                }
                if (count2 == 1){
                    if (isForbiddenMove(board_copy, newCoordinate) == NO){
                        num++;
                    }
                }
            }
        // 2-0-2 类型，可能在两个相反方向上形成不同的冲四，每个冲四只可能有一种成五方式
        }else if (count == 2){
            // 正方向的 2-0-2
            if (x + dx1 >= 0 && x + dx1 < SIZE && y + dy1 >= 0 && y + dy1 < SIZE && board_copy[x + dx1][y + dy1] == NOBODY){
                int dx_1 = dx1;
                int dy_1 = dy1;
                int count2 = 0;
                struct placeStone newCoordinate = {x + dx_1, y + dy_1};
                dx_1 += directions[i][0];
                dy_1 += directions[i][1];
                while (x + dx_1 >= 0 && x + dx_1 < SIZE && y + dy_1 >= 0 && y + dy_1 < SIZE && board_copy[x + dx_1][y + dy_1] == BLACK){
                    count2++;
                    dx_1 += directions[i][0];
                    dy_1 += directions[i][1];
                }
                if (count2 == 2){
                    if (isForbiddenMove(board_copy, newCoordinate) == NO){
                        num++;
                    }
                }
            }
            // 反方向的 2-0-2
            if (x + dx2 >= 0 && x + dx2 < SIZE && y + dy2 >= 0 && y + dy2 < SIZE && board_copy[x + dx2][y + dy2] == NOBODY){
                int dx_2 = dx2;
                int dy_2 = dy2;
                int count2 = 0;
                struct placeStone newCoordinate = {x + dx_2, y + dy_2};
                dx_2 -= directions[i][0];
                dy_2 -= directions[i][1];
                while (x + dx_2 >= 0 && x + dx_2 < SIZE && y + dy_2 >= 0 && y + dy_2 < SIZE && board_copy[x + dx_2][y + dy_2] == BLACK){
                    count2++;
                    dx_2 -= directions[i][0];
                    dy_2 -= directions[i][1];
                }
                if (count2 == 2){
                    if (isForbiddenMove(board_copy, newCoordinate) == NO){
                        num++;
                    }
                }
            }
        }
    }
    return num;
}

// 判断活四，返回活四的数量
int straightFour(int board[SIZE][SIZE], struct placeStone coordinate){
    int x = coordinate.x;
    int y = coordinate.y;
    int directions[4][2] = {{1, 0}, {0, 1}, {1, 1}, {1, -1}}; // 四个方向：水平、垂直、主对角线、副对角线
    int board_copy[SIZE][SIZE];
    int num = 0;

    copyBoard(board_copy, board); // 再构建一个棋盘副本
    board_copy[x][y] = BLACK;  // 假设落子

    // 遍历四个方向
    for (int i = 0; i < 4; i++){
        int count = 1;  // 连子数，包括当前位置
        int dx1 =  directions[i][0];
        int dy1 =  directions[i][1];
        int dx2 = -directions[i][0];
        int dy2 = -directions[i][1];

        // 向一个方向查找
        while (x + dx1 >= 0 && x + dx1 < SIZE && y + dy1 >= 0 && y + dy1 < SIZE && board_copy[x + dx1][y + dy1] == BLACK){
            count++;
            dx1 += directions[i][0];
            dy1 += directions[i][1];
        }

        // 向相反方向查找
        while (x + dx2 >= 0 && x + dx2 < SIZE && y + dy2 >= 0 && y + dy2 < SIZE && board_copy[x + dx2][y + dy2] == BLACK){
            count++;
            dx2 -= directions[i][0];
            dy2 -= directions[i][1];
        }

        // 四子连珠类型，一对方向上只有一种，但可能在两个方向形成五子连珠
        if (count == 4){
            // 判断两端是否能落子
            int available = 0; // 记录两端能落子的空位数量
            // 先看正方向一端能否落子
            if (x + dx1 >= 0 && x + dx1 < SIZE && y + dy1 >= 0 && y + dy1 < SIZE && board_copy[x + dx1][y + dy1] == NOBODY){
                struct placeStone newCoordinate = {x + dx1, y + dy1};
                if (isForbiddenMove(board_copy, newCoordinate) == NO){ // 判断第五颗棋子能否落下
                    available++;
                }
            }
            // 再看反方向一端能否落子
            if (x + dx2 >= 0 && x + dx2 < SIZE && y + dy2 >= 0 && y + dy2 < SIZE && board_copy[x + dx2][y + dy2] == NOBODY){
                struct placeStone newCoordinate = {x + dx2, y + dy2};
                if (isForbiddenMove(board_copy, newCoordinate) == NO){ // 判断第五颗棋子能否落下
                    available++;
                }
            }
            if (available == 2){
                num++;
            }
        }
    }
    return num;
}

// 判断活三，返回活三的数量
int three(int board[SIZE][SIZE], struct placeStone coordinate){
    int x = coordinate.x;
    int y = coordinate.y;
    int directions[4][2] = {{1, 0}, {0, 1}, {1, 1}, {1, -1}}; // 四个方向：水平、垂直、主对角线、副对角线
    int board_copy[SIZE][SIZE];
    int num = 0;

    copyBoard(board_copy, board); // 再构建一个棋盘副本
    board_copy[x][y] = BLACK;  // 假设落子

    // 遍历四个方向
    for (int i = 0; i < 4; i++){
        int count = 1;  // 连子数，包括当前位置
        int dx1 =  directions[i][0];
        int dy1 =  directions[i][1];
        int dx2 = -directions[i][0];
        int dy2 = -directions[i][1];

        // 向一个方向查找
        while (x + dx1 >= 0 && x + dx1 < SIZE && y + dy1 >= 0 && y + dy1 < SIZE && board_copy[x + dx1][y + dy1] == BLACK){
            count++;
            dx1 += directions[i][0];
            dy1 += directions[i][1];
        }

        // 向相反方向查找
        while (x + dx2 >= 0 && x + dx2 < SIZE && y + dy2 >= 0 && y + dy2 < SIZE && board_copy[x + dx2][y + dy2] == BLACK){
            count++;
            dx2 -= directions[i][0];
            dy2 -= directions[i][1];
        }

        // 三子连珠类型，可能在两个方向形成四子连珠，为了判断四子连珠是不是活四，又要验证两端能否成五
        if (count == 3){
            // 判断两端是否能落子
            int avail_four = 0; // 记录两端能先形成活四的数量

            // 先看正方向一端能否落子形成四子连珠
            if (x + dx1 >= 0 && x + dx1 < SIZE && y + dy1 >= 0 && y + dy1 < SIZE && board_copy[x + dx1][y + dy1] == NOBODY){
                int dx_1 = dx1;
                int dy_1 = dy1;
                int dx_2 = dx2;
                int dy_2 = dy2;
                struct placeStone newCoordinate = {x + dx_1, y + dy_1};
                if (isForbiddenMove(board_copy, newCoordinate) == NO){ // 判断第四颗棋子能否落下
                    int avail_five = 0; // 记录四子连珠两端能形成五连的数量
                    board_copy[newCoordinate.x][newCoordinate.y] = BLACK; // 假设落下了第四颗棋子
                    // 正方向多看一格
                    dx_1 += directions[i][0];
                    dy_1 += directions[i][1];
                    // 看一看正方向第五个是不是空位
                    if (x + dx_1 >= 0 && x + dx_1 < SIZE && y + dy_1 >= 0 && y + dy_1 < SIZE && board_copy[x + dx_1][y + dy_1] == NOBODY){
                        struct placeStone newCoordinate = {x + dx_1, y + dy_1};
                        if (isForbiddenMove(board_copy, newCoordinate) == NO){ // 判断第五颗棋子能否落下
                            avail_five++;
                        }
                    }
                    // 看一看反方向第五个是不是空位
                    if (x + dx_2 >= 0 && x + dx_2 < SIZE && y + dy_2 >= 0 && y + dy_2 < SIZE && board_copy[x + dx_2][y + dy_2] == NOBODY){
                        struct placeStone newCoordinate = {x + dx_2, y + dy_2};
                        if (isForbiddenMove(board_copy, newCoordinate) == NO){ // 判断第五颗棋子能否落下
                            avail_five++;
                        }
                    }

                    // 判断正方向这个四子连珠是不是活四，是的话 avail_four 加一
                    if (avail_five == 2){
                        avail_four++;
                    }
                    board_copy[newCoordinate.x][newCoordinate.y] = NOBODY; // 撤销落下的第四颗棋子
                }
            }

            // 再看反方向一端能否落子形成四子连珠
            if (x + dx2 >= 0 && x + dx2 < SIZE && y + dy2 >= 0 && y + dy2 < SIZE && board_copy[x + dx2][y + dy2] == NOBODY){
                int dx_1 = dx1;
                int dy_1 = dy1;
                int dx_2 = dx2;
                int dy_2 = dy2;
                struct placeStone newCoordinate = {x + dx_2, y + dy_2};
                if (isForbiddenMove(board_copy, newCoordinate) == NO){ // 判断第四颗棋子能否落下
                    int avail_five = 0; // 记录四子连珠两端能形成五连的数量
                    board_copy[newCoordinate.x][newCoordinate.y] = BLACK; // 假设落下了第四颗棋子
                    // 反方向多看一格
                    dx_2 -= directions[i][0];
                    dy_2 -= directions[i][1];
                    // 看一看正方向第五个是不是空位
                    if (x + dx_1 >= 0 && x + dx_1 < SIZE && y + dy_1 >= 0 && y + dy_1 < SIZE && board_copy[x + dx_1][y + dy_1] == NOBODY){
                        struct placeStone newCoordinate = {x + dx_1, y + dy_1};
                        if (isForbiddenMove(board_copy, newCoordinate) == NO){ // 判断第五颗棋子能否落下
                            avail_five++;
                        }
                    }
                    // 看一看反方向第五个是不是空位
                    if (x + dx_2 >= 0 && x + dx_2 < SIZE && y + dy_2 >= 0 && y + dy_2 < SIZE && board_copy[x + dx_2][y + dy_2] == NOBODY){
                        struct placeStone newCoordinate = {x + dx_2, y + dy_2};
                        if (isForbiddenMove(board_copy, newCoordinate) == NO){ // 判断第五颗棋子能否落下
                            avail_five++;
                        }
                    }

                    // 判断正方向这个四子连珠是不是活四，是的话 avail_four 加一
                    if (avail_five == 2){
                        avail_four++;
                    }
                    board_copy[newCoordinate.x][newCoordinate.y] = NOBODY; // 撤销落下的第四颗棋子
                }
            }

            if (avail_four > 0){
                num++;
            }

        // 1-0-2 类型，可能在两个相反方向上形成不同的活三，每个活三只有一种成活四方式
        }else if (count == 1){

            // 正方向的 1-0-2
            if (x + dx1 >= 0 && x + dx1 < SIZE && y + dy1 >= 0 && y + dy1 < SIZE && board_copy[x + dx1][y + dy1] == NOBODY){ // 判断是不是空位
                int dx_1 = dx1;
                int dy_1 = dy1;
                int dx_2 = dx2;
                int dy_2 = dy2;
                int count2 = 0;
                struct placeStone newCoordinate = {x + dx_1, y + dy_1};
                // 跳过空位数二子连珠
                dx_1 += directions[i][0];
                dy_1 += directions[i][1];
                while (x + dx_1 >= 0 && x + dx_1 < SIZE && y + dy_1 >= 0 && y + dy_1 < SIZE && board_copy[x + dx_1][y + dy_1] == BLACK){
                    count2++;
                    dx_1 += directions[i][0];
                    dy_1 += directions[i][1];
                }
                if (count2 == 2){
                    if (isForbiddenMove(board_copy, newCoordinate) == NO){ // 判断第四颗棋子能否落下
                        int avail_five = 0; // 记录四子连珠两端能形成五连的数量
                        board_copy[newCoordinate.x][newCoordinate.y] = BLACK; // 假设落下了第四颗棋子
                        // 看一看正方向第五个是不是空位
                        if (x + dx_1 >= 0 && x + dx_1 < SIZE && y + dy_1 >= 0 && y + dy_1 < SIZE && board_copy[x + dx_1][y + dy_1] == NOBODY){
                            struct placeStone newCoordinate = {x + dx_1, y + dy_1};
                            if (isForbiddenMove(board_copy, newCoordinate) == NO){ // 判断第五颗棋子能否落下
                                avail_five++;
                            }
                        }
                        // 看一看反方向第五个是不是空位
                        if (x + dx_2 >= 0 && x + dx_2 < SIZE && y + dy_2 >= 0 && y + dy_2 < SIZE && board_copy[x + dx_2][y + dy_2] == NOBODY){
                            struct placeStone newCoordinate = {x + dx_2, y + dy_2};
                            if (isForbiddenMove(board_copy, newCoordinate) == NO){ // 判断第五颗棋子能否落下
                                avail_five++;
                            }
                        }
                        
                        // 判断这个 1-0-2 能否形成活四
                        if (avail_five == 2){
                            num++;
                        }
                        board_copy[newCoordinate.x][newCoordinate.y] = NOBODY; // 撤销落下的第四颗棋子
                    }
                }
            }
            
            // 反方向的 1-0-2
            if (x + dx2 >= 0 && x + dx2 < SIZE && y + dy2 >= 0 && y + dy2 < SIZE && board_copy[x + dx2][y + dy2] == NOBODY){ // 判断是不是空位
                int dx_1 = dx1;
                int dy_1 = dy1;
                int dx_2 = dx2;
                int dy_2 = dy2;
                int count2 = 0;
                struct placeStone newCoordinate = {x + dx_2, y + dy_2};
                // 跳过空位数二子连珠
                dx_2 -= directions[i][0];
                dy_2 -= directions[i][1];
                while (x + dx_2 >= 0 && x + dx_2 < SIZE && y + dy_2 >= 0 && y + dy_2 < SIZE && board_copy[x + dx_2][y + dy_2] == BLACK){
                    count2++;
                    dx_2 -= directions[i][0];
                    dy_2 -= directions[i][1];
                }
                if (count2 == 2){
                    if (isForbiddenMove(board_copy, newCoordinate) == NO){ // 判断第四颗棋子能否落下
                        int avail_five = 0; // 记录四子连珠两端能形成五连的数量
                        board_copy[newCoordinate.x][newCoordinate.y] = BLACK; // 假设落下了第四颗棋子
                        // 看一看正方向第五个是不是空位
                        if (x + dx_1 >= 0 && x + dx_1 < SIZE && y + dy_1 >= 0 && y + dy_1 < SIZE && board_copy[x + dx_1][y + dy_1] == NOBODY){
                            struct placeStone newCoordinate = {x + dx_1, y + dy_1};
                            if (isForbiddenMove(board_copy, newCoordinate) == NO){ // 判断第五颗棋子能否落下
                                avail_five++;
                            }
                        }
                        // 看一看反方向第五个是不是空位
                        if (x + dx_2 >= 0 && x + dx_2 < SIZE && y + dy_2 >= 0 && y + dy_2 < SIZE && board_copy[x + dx_2][y + dy_2] == NOBODY){
                            struct placeStone newCoordinate = {x + dx_2, y + dy_2};
                            if (isForbiddenMove(board_copy, newCoordinate) == NO){ // 判断第五颗棋子能否落下
                                avail_five++;
                            }
                        }
                        
                        // 判断这个 1-0-2 能否形成活四
                        if (avail_five == 2){
                            num++;
                        }
                        board_copy[newCoordinate.x][newCoordinate.y] = NOBODY; // 撤销落下的第四颗棋子
                    }
                }
            }

        // 2-0-1 类型，可能在两个相反方向上形成不同的活三，每个活三只有一种成活四方式
        }else if (count == 2){
          
            // 正方向的 2-0-1
            if (x + dx1 >= 0 && x + dx1 < SIZE && y + dy1 >= 0 && y + dy1 < SIZE && board_copy[x + dx1][y + dy1] == NOBODY){ // 判断是不是空位
                int dx_1 = dx1;
                int dy_1 = dy1;
                int dx_2 = dx2;
                int dy_2 = dy2;
                int count2 = 0;
                struct placeStone newCoordinate = {x + dx_1, y + dy_1};
                // 跳过空位数最后一子
                dx_1 += directions[i][0];
                dy_1 += directions[i][1];
                while (x + dx_1 >= 0 && x + dx_1 < SIZE && y + dy_1 >= 0 && y + dy_1 < SIZE && board_copy[x + dx_1][y + dy_1] == BLACK){
                    count2++;
                    dx_1 += directions[i][0];
                    dy_1 += directions[i][1];
                }
                if (count2 == 1){
                    if (isForbiddenMove(board_copy, newCoordinate) == NO){ // 判断第四颗棋子能否落下
                        int avail_five = 0; // 记录四子连珠两端能形成五连的数量
                        board_copy[newCoordinate.x][newCoordinate.y] = BLACK; // 假设落下了第四颗棋子
                        // 看一看正方向第五个是不是空位
                        if (x + dx_1 >= 0 && x + dx_1 < SIZE && y + dy_1 >= 0 && y + dy_1 < SIZE && board_copy[x + dx_1][y + dy_1] == NOBODY){
                            struct placeStone newCoordinate = {x + dx_1, y + dy_1};
                            if (isForbiddenMove(board_copy, newCoordinate) == NO){ // 判断第五颗棋子能否落下
                                avail_five++;
                            }
                        }
                        // 看一看反方向第五个是不是空位
                        if (x + dx_2 >= 0 && x + dx_2 < SIZE && y + dy_2 >= 0 && y + dy_2 < SIZE && board_copy[x + dx_2][y + dy_2] == NOBODY){
                            struct placeStone newCoordinate = {x + dx_2, y + dy_2};
                            if (isForbiddenMove(board_copy, newCoordinate) == NO){ // 判断第五颗棋子能否落下
                                avail_five++;
                            }
                        }
                        
                        // 判断这个 2-0-1 能否形成活四
                        if (avail_five == 2){
                            num++;
                        }
                        board_copy[newCoordinate.x][newCoordinate.y] = NOBODY; // 撤销落下的第四颗棋子
                    }
                }
            }

            // 反方向的 2-0-1
            if (x + dx2 >= 0 && x + dx2 < SIZE && y + dy2 >= 0 && y + dy2 < SIZE && board_copy[x + dx2][y + dy2] == NOBODY){ // 判断是不是空位
                int dx_1 = dx1;
                int dy_1 = dy1;
                int dx_2 = dx2;
                int dy_2 = dy2;
                int count2 = 0;
                struct placeStone newCoordinate = {x + dx_2, y + dy_2};
                // 跳过空位数最后一子
                dx_2 -= directions[i][0];
                dy_2 -= directions[i][1];
                while (x + dx_2 >= 0 && x + dx_2 < SIZE && y + dy_2 >= 0 && y + dy_2 < SIZE && board_copy[x + dx_2][y + dy_2] == BLACK){
                    count2++;
                    dx_2 -= directions[i][0];
                    dy_2 -= directions[i][1];
                }
                if (count2 == 1){
                    if (isForbiddenMove(board_copy, newCoordinate) == NO){ // 判断第四颗棋子能否落下
                        int avail_five = 0; // 记录四子连珠两端能形成五连的数量
                        board_copy[newCoordinate.x][newCoordinate.y] = BLACK; // 假设落下了第四颗棋子
                        // 看一看正方向第五个是不是空位
                        if (x + dx_1 >= 0 && x + dx_1 < SIZE && y + dy_1 >= 0 && y + dy_1 < SIZE && board_copy[x + dx_1][y + dy_1] == NOBODY){
                            struct placeStone newCoordinate = {x + dx_1, y + dy_1};
                            if (isForbiddenMove(board_copy, newCoordinate) == NO){ // 判断第五颗棋子能否落下
                                avail_five++;
                            }
                        }
                        // 看一看反方向第五个是不是空位
                        if (x + dx_2 >= 0 && x + dx_2 < SIZE && y + dy_2 >= 0 && y + dy_2 < SIZE && board_copy[x + dx_2][y + dy_2] == NOBODY){
                            struct placeStone newCoordinate = {x + dx_2, y + dy_2};
                            if (isForbiddenMove(board_copy, newCoordinate) == NO){ // 判断第五颗棋子能否落下
                                avail_five++;
                            }
                        }
                        
                        // 判断这个 2-0-1 能否形成活四
                        if (avail_five == 2){
                            num++;
                        }
                        board_copy[newCoordinate.x][newCoordinate.y] = NOBODY; // 撤销落下的第四颗棋子
                    }
                }
            }
        }
    }
    return num;
}

// 复制虚拟棋盘的副本
void copyBoard(int to[SIZE][SIZE], int from[SIZE][SIZE]){
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            to[i][j] = from[i][j];
        }
    }
}