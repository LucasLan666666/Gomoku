// 此文件用于对冲四的判断
#include "gomoku.h"

// 判断冲四，返回冲四的数量
int four(int board[SIZE][SIZE], struct placeStone coordinate, int player){
    int x = coordinate.x;
    int y = coordinate.y;
    int directions[4][2] = {{1, 0}, {0, 1}, {1, 1}, {1, -1}}; // 四个方向：水平、垂直、主对角线、副对角线
    int board_copy[SIZE][SIZE];
    int num = 0;

    copyBoard(board_copy, board); // 再构建一个棋盘副本
    board_copy[x][y] = player;  // 假设落子

    // 遍历四个方向
    for (int i = 0; i < 4; i++){
        int count = 1;  // 连子数，包括当前位置
        int dx1 =  directions[i][0];
        int dy1 =  directions[i][1];
        int dx2 = -directions[i][0];
        int dy2 = -directions[i][1];

        // 向一个方向查找
        while (x + dx1 >= 0 && x + dx1 < SIZE && y + dy1 >= 0 && y + dy1 < SIZE && board_copy[x + dx1][y + dy1] == player){
            count++;
            dx1 += directions[i][0];
            dy1 += directions[i][1];
        }

        // 向相反方向查找
        while (x + dx2 >= 0 && x + dx2 < SIZE && y + dy2 >= 0 && y + dy2 < SIZE && board_copy[x + dx2][y + dy2] == player){
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
                if (isForbiddenMove(board_copy, newCoordinate, player) == NO){ // 判断第五颗棋子能否落下
                    available++;
                }
            }
            // 再看反方向一端能否落子
            if (x + dx2 >= 0 && x + dx2 < SIZE && y + dy2 >= 0 && y + dy2 < SIZE && board_copy[x + dx2][y + dy2] == NOBODY){
                struct placeStone newCoordinate = {x + dx2, y + dy2};
                if (isForbiddenMove(board_copy, newCoordinate, player) == NO){ // 判断第五颗棋子能否落下
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
                while (x + dx_1 >= 0 && x + dx_1 < SIZE && y + dy_1 >= 0 && y + dy_1 < SIZE && board_copy[x + dx_1][y + dy_1] == player){
                    count2++;
                    dx_1 += directions[i][0];
                    dy_1 += directions[i][1];
                }
                if (count2 == 3){
                    if (isForbiddenMove(board_copy, newCoordinate, player) == NO){
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
                while (x + dx_2 >= 0 && x + dx_2 < SIZE && y + dy_2 >= 0 && y + dy_2 < SIZE && board_copy[x + dx_2][y + dy_2] == player){
                    count2++;
                    dx_2 -= directions[i][0];
                    dy_2 -= directions[i][1];
                }
                if (count2 == 3){
                    if (isForbiddenMove(board_copy, newCoordinate, player) == NO){
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
                while (x + dx_1 >= 0 && x + dx_1 < SIZE && y + dy_1 >= 0 && y + dy_1 < SIZE && board_copy[x + dx_1][y + dy_1] == player){
                    count2++;
                    dx_1 += directions[i][0];
                    dy_1 += directions[i][1];
                }
                if (count2 == 1){
                    if (isForbiddenMove(board_copy, newCoordinate, player) == NO){
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
                while (x + dx_2 >= 0 && x + dx_2 < SIZE && y + dy_2 >= 0 && y + dy_2 < SIZE && board_copy[x + dx_2][y + dy_2] == player){
                    count2++;
                    dx_2 -= directions[i][0];
                    dy_2 -= directions[i][1];
                }
                if (count2 == 1){
                    if (isForbiddenMove(board_copy, newCoordinate, player) == NO){
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
                while (x + dx_1 >= 0 && x + dx_1 < SIZE && y + dy_1 >= 0 && y + dy_1 < SIZE && board_copy[x + dx_1][y + dy_1] == player){
                    count2++;
                    dx_1 += directions[i][0];
                    dy_1 += directions[i][1];
                }
                if (count2 == 2){
                    if (isForbiddenMove(board_copy, newCoordinate, player) == NO){
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
                while (x + dx_2 >= 0 && x + dx_2 < SIZE && y + dy_2 >= 0 && y + dy_2 < SIZE && board_copy[x + dx_2][y + dy_2] == player){
                    count2++;
                    dx_2 -= directions[i][0];
                    dy_2 -= directions[i][1];
                }
                if (count2 == 2){
                    if (isForbiddenMove(board_copy, newCoordinate, player) == NO){
                        num++;
                    }
                }
            }
        }
    }
    return num;
}
