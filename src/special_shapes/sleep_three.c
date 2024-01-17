// 此文件用于对眠三的判断
// 因为没查到眠三的英语，所以我擅自命名为 “sleepThree”
#include "../gomoku.h"

// 判断眠三，返回眠三可以形成冲四种类的数量
int sleepThree(signed char board[SIZE][SIZE], Coordinate coordinate, signed char player) {
    signed char x = coordinate.x;
    signed char y = coordinate.y;
    signed char directions[4][2] = {{1, 0}, {0, 1}, {1, 1}, {1, -1}}; // 四个方向：水平、垂直、主对角线、副对角线
    signed char board_copy[SIZE][SIZE];
    int num = 0;

    copyBoard(board_copy, board); // 再构建一个棋盘副本
    board_copy[x][y] = player; // 假设落子

    // 遍历四个方向
    for (int i = 0; i < 4; i++) {
        int count = 1; // 连子数，包括当前位置
        signed char dx1 =  directions[i][0];
        signed char dy1 =  directions[i][1];
        signed char dx2 = -directions[i][0];
        signed char dy2 = -directions[i][1];

        // 向一个方向查找
        while (x + dx1 >= 0 && x + dx1 < SIZE && y + dy1 >= 0 && y + dy1 < SIZE && board_copy[x + dx1][y + dy1] == player) {
            count++;
            dx1 += directions[i][0];
            dy1 += directions[i][1];
        }

        // 向相反方向查找
        while (x + dx2 >= 0 && x + dx2 < SIZE && y + dy2 >= 0 && y + dy2 < SIZE && board_copy[x + dx2][y + dy2] == player) {
            count++;
            dx2 -= directions[i][0];
            dy2 -= directions[i][1];
        }

        if (count == 3) {
        // 三子连珠类型，可能在两个方向形成四子连珠或者跳冲四

            // 判断两端是否能落子
            int avail_straightFour = 0; // 记录两端能先形成活四的数量
            int avail_four = 0; // 记录两端能形成冲四的数量

            // 先看正方向一端能否落子形成四子连珠
            if (x + dx1 >= 0 && x + dx1 < SIZE && y + dy1 >= 0 && y + dy1 < SIZE && board_copy[x + dx1][y + dy1] == NOBODY) {
                signed char dx_1 = dx1;
                signed char dy_1 = dy1;
                signed char dx_2 = dx2;
                signed char dy_2 = dy2;
                Coordinate newCoordinate = {x + dx_1, y + dy_1};
                if (isForbiddenMove(board_copy, newCoordinate, player) == NO) { // 判断第四颗棋子能否落下
                    int avail_five = 0; // 记录四子连珠两端能形成五连的数量
                    board_copy[newCoordinate.x][newCoordinate.y] = player; // 假设落下了第四颗棋子
                    // 正方向多看一格
                    dx_1 += directions[i][0];
                    dy_1 += directions[i][1];

                    // 看一看正方向第五个是不是空位
                    if (x + dx_1 >= 0 && x + dx_1 < SIZE && y + dy_1 >= 0 && y + dy_1 < SIZE && board_copy[x + dx_1][y + dy_1] == NOBODY) {
                        Coordinate newCoordinate = {x + dx_1, y + dy_1};
                        // 多看一格，确保不是长连
                        dx_1 += directions[i][0];
                        dy_1 += directions[i][1];
                        if (x + dx_1 < 0 || x + dx_1 >= SIZE || y + dy_1 < 0 || y + dy_1 >= SIZE || board_copy[x + dx_1][y + dy_1] != player) {                      
                            if (isForbiddenMove(board_copy, newCoordinate, player) == NO) { // 判断第五颗棋子能否落下
                                avail_five++;
                            }
                        }
                        // 撤销多看的一格
                        dx_1 -= directions[i][0];
                        dy_1 -= directions[i][1];
                    }
                    // 看一看反方向第五个是不是空位
                    if (x + dx_2 >= 0 && x + dx_2 < SIZE && y + dy_2 >= 0 && y + dy_2 < SIZE && board_copy[x + dx_2][y + dy_2] == NOBODY) {
                        Coordinate newCoordinate = {x + dx_2, y + dy_2};
                        // 多看一格，确保不是长连
                        dx_2 -= directions[i][0];
                        dy_2 -= directions[i][1];
                        if (x + dx_2 < 0 || x + dx_2 >= SIZE || y + dy_2 < 0 || y + dy_2 >= SIZE || board_copy[x + dx_2][y + dy_2] != player) {  
                            if (isForbiddenMove(board_copy, newCoordinate, player) == NO) { // 判断第五颗棋子能否落下
                                avail_five++;
                            }
                        }
                        // 撤销多看的一格
                        dx_2 += directions[i][0];
                        dy_2 += directions[i][1];
                    }

                    // 判断正方向这个四子连珠是不是活四，是的话 avail_straightFour 加一
                    if (avail_five == 2) {
                        avail_straightFour++;
                    // 判断正方向这个四子连珠是不是冲四，是的话 avail_four 加一
                    } else if (avail_five == 1) {
                        avail_four++;
                    }
                    board_copy[newCoordinate.x][newCoordinate.y] = NOBODY; // 撤销落下的第四颗棋子
                }
            }

            // 再看反方向一端能否落子形成四子连珠
            if (x + dx2 >= 0 && x + dx2 < SIZE && y + dy2 >= 0 && y + dy2 < SIZE && board_copy[x + dx2][y + dy2] == NOBODY) {
                signed char dx_1 = dx1;
                signed char dy_1 = dy1;
                signed char dx_2 = dx2;
                signed char dy_2 = dy2;
                Coordinate newCoordinate = {x + dx_2, y + dy_2};
                if (isForbiddenMove(board_copy, newCoordinate, player) == NO) { // 判断第四颗棋子能否落下
                    int avail_five = 0; // 记录四子连珠两端能形成五连的数量
                    board_copy[newCoordinate.x][newCoordinate.y] = player; // 假设落下了第四颗棋子
                    // 反方向多看一格
                    dx_2 -= directions[i][0];
                    dy_2 -= directions[i][1];

                    // 看一看正方向第五个是不是空位
                    if (x + dx_1 >= 0 && x + dx_1 < SIZE && y + dy_1 >= 0 && y + dy_1 < SIZE && board_copy[x + dx_1][y + dy_1] == NOBODY) {
                        Coordinate newCoordinate = {x + dx_1, y + dy_1};
                        // 多看一格，确保不是长连
                        dx_1 += directions[i][0];
                        dy_1 += directions[i][1];
                        if (x + dx_1 < 0 || x + dx_1 >= SIZE || y + dy_1 < 0 || y + dy_1 >= SIZE || board_copy[x + dx_1][y + dy_1] != player) {                      
                            if (isForbiddenMove(board_copy, newCoordinate, player) == NO) { // 判断第五颗棋子能否落下
                                avail_five++;
                            }
                        }
                        // 撤销多看的一格
                        dx_1 -= directions[i][0];
                        dy_1 -= directions[i][1];
                    }
                    // 看一看反方向第五个是不是空位
                    if (x + dx_2 >= 0 && x + dx_2 < SIZE && y + dy_2 >= 0 && y + dy_2 < SIZE && board_copy[x + dx_2][y + dy_2] == NOBODY) {
                        Coordinate newCoordinate = {x + dx_2, y + dy_2};
                        // 多看一格，确保不是长连
                        dx_2 -= directions[i][0];
                        dy_2 -= directions[i][1];
                        if (x + dx_2 < 0 || x + dx_2 >= SIZE || y + dy_2 < 0 || y + dy_2 >= SIZE || board_copy[x + dx_2][y + dy_2] != player) {  
                            if (isForbiddenMove(board_copy, newCoordinate, player) == NO) { // 判断第五颗棋子能否落下
                                avail_five++;
                            }
                        }
                        // 撤销多看的一格
                        dx_2 += directions[i][0];
                        dy_2 += directions[i][1];
                    }

                    // 判断反方向这个四子连珠是不是活四，是的话 avail_straightFour 加一
                    if (avail_five == 2) {
                        avail_straightFour++;
                    // 判断反方向这个四子连珠是不是冲四，是的话 avail_four 加一
                    } else if (avail_five == 1) {
                        avail_four++;
                    }
                    board_copy[newCoordinate.x][newCoordinate.y] = NOBODY; // 撤销落下的第四颗棋子
                }
            }

            // 先看正方向一端能否落子形成 3-0-1 跳冲四
            if (x + dx1 >= 0 && x + dx1 < SIZE && y + dy1 >= 0 && y + dy1 < SIZE && board_copy[x + dx1][y + dy1] == NOBODY) {
                signed char dx_1 = dx1;
                signed char dy_1 = dy1;
               // 跳过空位多看一格
                dx_1 += directions[i][0];
                dy_1 += directions[i][1];
                Coordinate newCoordinate1 = {x + dx_1, y + dy_1}; // 3-0-1 跳冲四的第四颗棋子
                Coordinate newCoordinate2 = {x + dx_1 - directions[i][0], y + dy_1 - directions[i][1]}; // 3-0-1 跳冲四的第五颗棋子
                if (x + dx_1 >= 0 && x + dx_1 < SIZE && y + dy_1 >= 0 && y + dy_1 < SIZE && board_copy[x + dx_1][y + dy_1] == NOBODY) {
                    if (isForbiddenMove(board_copy, newCoordinate1, player) == NO) { // 判断第四颗棋子能否落下
                        board_copy[newCoordinate1.x][newCoordinate1.y] = player; // 假设落下了第四颗棋子
                        // 正方向多看一格，排除长连的情况
                        dx_1 += directions[i][0];
                        dy_1 += directions[i][1];
                        if (x + dx_1 >= 0 && x + dx_1 < SIZE && y + dy_1 >= 0 && y + dy_1 < SIZE && board_copy[x + dx_1][y + dy_1] != player) {
                            if (isForbiddenMove(board_copy, newCoordinate2, player) == NO) { // 判断第五颗棋子能否落下
                                avail_four++;
                            }
                        }
                        board_copy[newCoordinate1.x][newCoordinate1.y] = NOBODY; // 撤销落下的第四颗棋子
                    }
                }
            }

            // 再看反方向一端能否落子形成 3-0-1 跳冲四
            if (x + dx2 >= 0 && x + dx2 < SIZE && y + dy2 >= 0 && y + dy2 < SIZE && board_copy[x + dx2][y + dy2] == NOBODY) {
                signed char dx_2 = dx2;
                signed char dy_2 = dy2;
                // 跳过空位多看一格
                dx_2 -= directions[i][0];
                dy_2 -= directions[i][1];
                Coordinate newCoordinate1 = {x + dx_2, y + dy_2}; // 3-0-1 跳冲四的第四颗棋子
                Coordinate newCoordinate2 = {x + dx_2 + directions[i][0], y + dy_2 + directions[i][1]}; // 3-0-1 跳冲四的第五颗棋子
                if (x + dx_2 >= 0 && x + dx_2 < SIZE && y + dy_2 >= 0 && y + dy_2 < SIZE && board_copy[x + dx_2][y + dy_2] == NOBODY) {
                    if (isForbiddenMove(board_copy, newCoordinate1, player) == NO) { // 判断第四颗棋子能否落下
                        board_copy[newCoordinate1.x][newCoordinate1.y] = player; // 假设落下了第四颗棋子
                        // 反方向多看一格，排除长连的情况
                        dx_2 -= directions[i][0];
                        dy_2 -= directions[i][1];
                        if (x + dx_2 >= 0 && x + dx_2 < SIZE && y + dy_2 >= 0 && y + dy_2 < SIZE && board_copy[x + dx_2][y + dy_2] != player) {
                            if (isForbiddenMove(board_copy, newCoordinate2, player) == NO) { // 判断第五颗棋子能否落下
                                avail_four++;
                            }
                        }
                        board_copy[newCoordinate1.x][newCoordinate1.y] = NOBODY; // 撤销落下的第四颗棋子
                    }
                }
            }

            // 没有一端能形成活四时，数一下能形成冲四的数量
            if (avail_straightFour == 0) {
                num += avail_four;
            }

        } else if (count == 1) {
        // 1-0-2 类型，可能在两个相反方向上形成不同的眠三，每个眠三有三种成冲四方式
        // 1-0-0-2 类型，可能在两个相反方向上形成不同的眠三，每个眠三有两种成冲四方式
        // 1-0-1-0-1 类型（1 在边界），可能在两个相反方向上形成不同的眠三，每个眠三有两种成冲四方式
        // 1-0-1-0-1 类型（1 在中央），只可能形成这一种眠三，有两种成冲四方式


            // 正方向的 1-0-2
            if (x + dx1 >= 0 && x + dx1 < SIZE && y + dy1 >= 0 && y + dy1 < SIZE && board_copy[x + dx1][y + dy1] == NOBODY) { // 判断是不是空位
                signed char dx_1 = dx1;
                signed char dy_1 = dy1;
                signed char dx_2 = dx2;
                signed char dy_2 = dy2;
                int count2 = 0;
                Coordinate newCoordinate1 = {x + directions[i][0], y + directions[i][1]}; // 四子连珠类型冲四的第四颗棋子
                Coordinate newCoordinate2 = {x - directions[i][0], y - directions[i][1]}; // 2-0-2 跳冲四的第四颗棋子
                Coordinate newCoordinate3 = {x + 4*directions[i][0], y + 4*directions[i][1]}; // 1-0-3 跳冲四的第四颗棋子
                // 跳过空位数二子连珠
                dx_1 += directions[i][0];
                dy_1 += directions[i][1];
                while (x + dx_1 >= 0 && x + dx_1 < SIZE && y + dy_1 >= 0 && y + dy_1 < SIZE && board_copy[x + dx_1][y + dy_1] == player) {
                    count2++;
                    dx_1 += directions[i][0];
                    dy_1 += directions[i][1];
                }
                if (count2 == 2) {
                    // 判断四子连珠的冲四
                    if (isForbiddenMove(board_copy, newCoordinate1, player) == NO) { // 判断第四颗棋子能否落下
                        int avail_five = 0; // 记录四子连珠两端能形成五连的数量
                        board_copy[newCoordinate1.x][newCoordinate1.y] = player; // 假设落下了第四颗棋子

                        // 看一看正方向第五个是不是空位
                        if (x + dx_1 >= 0 && x + dx_1 < SIZE && y + dy_1 >= 0 && y + dy_1 < SIZE && board_copy[x + dx_1][y + dy_1] == NOBODY) {
                            Coordinate newCoordinate = {x + dx_1, y + dy_1};
                            // 多看一格，确保不是长连
                            dx_1 += directions[i][0];
                            dy_1 += directions[i][1];
                            if (x + dx_1 < 0 || x + dx_1 >= SIZE || y + dy_1 < 0 || y + dy_1 >= SIZE || board_copy[x + dx_1][y + dy_1] != player) {
                                if (isForbiddenMove(board_copy, newCoordinate, player) == NO) { // 判断第五颗棋子能否落下
                                    avail_five++;
                                }
                            }
                            // 撤销多看的一格
                            dx_1 -= directions[i][0];
                            dy_1 -= directions[i][1];
                        }
                        // 看一看反方向第五个是不是空位
                        if (x + dx_2 >= 0 && x + dx_2 < SIZE && y + dy_2 >= 0 && y + dy_2 < SIZE && board_copy[x + dx_2][y + dy_2] == NOBODY) {
                            Coordinate newCoordinate = {x + dx_2, y + dy_2};
                            // 多看一格，确保不是长连
                            dx_2 -= directions[i][0];
                            dy_2 -= directions[i][1];
                            if (x + dx_2 < 0 || x + dx_2 >= SIZE || y + dy_2 < 0 || y + dy_2 >= SIZE || board_copy[x + dx_2][y + dy_2] != player) {
                                if (isForbiddenMove(board_copy, newCoordinate, player) == NO) { // 判断第五颗棋子能否落下
                                    avail_five++;
                                }
                            }
                            // 撤销多看的一格
                            dx_2 += directions[i][0];
                            dy_2 += directions[i][1];
                        }
                        
                        // 判断能否形成四子连珠的冲四
                        if (avail_five == 1) {
                            num++;
                        }
                        board_copy[newCoordinate1.x][newCoordinate1.y] = NOBODY; // 撤销落下的第四颗棋子
                    }

                    // 判断 2-0-2 跳冲四
                    if (   newCoordinate2.x >= 0 && newCoordinate2.x < SIZE
                        && newCoordinate2.y >= 0 && newCoordinate2.y < SIZE
                        && board_copy[newCoordinate2.x][newCoordinate2.y] == NOBODY
                        && (   newCoordinate2.x - directions[i][0] < 0 || newCoordinate2.x - directions[i][0] >= SIZE
                            || newCoordinate2.y - directions[i][1] < 0 || newCoordinate2.y - directions[i][1] >= SIZE
                            || board_copy[newCoordinate2.x - directions[i][0]][newCoordinate2.y - directions[i][1]] != player)) { // 判断是不是空位，并同时排除可能的长连
                        if (isForbiddenMove(board_copy, newCoordinate2, player) == NO) { // 判断第四颗棋子能否落下
                            board_copy[newCoordinate2.x][newCoordinate2.y] = player; // 假设落下了第四颗棋子

                            // 看一看能不能落下第五颗棋子
                            if (isForbiddenMove(board_copy, newCoordinate1, player) == NO) { // 判断第五颗棋子能否落下
                                num++;
                            }
                            board_copy[newCoordinate2.x][newCoordinate2.y] = NOBODY; // 撤销落下的第四颗棋子
                        }
                    }

                    // 判断 1-0-3 跳冲四
                    if (   newCoordinate3.x >= 0 && newCoordinate3.x < SIZE
                        && newCoordinate3.y >= 0 && newCoordinate3.y < SIZE
                        && board_copy[newCoordinate3.x][newCoordinate3.y] == NOBODY
                        && (   newCoordinate3.x + directions[i][0] < 0 || newCoordinate3.x + directions[i][0] >= SIZE
                            || newCoordinate3.y + directions[i][1] < 0 || newCoordinate3.y + directions[i][1] >= SIZE
                            || board_copy[newCoordinate3.x + directions[i][0]][newCoordinate3.y + directions[i][1]] != player)) { // 判断是不是空位，并同时排除可能的长连
                        if (isForbiddenMove(board_copy, newCoordinate3, player) == NO) { // 判断第四颗棋子能否落下
                            board_copy[newCoordinate3.x][newCoordinate3.y] = player; // 假设落下了第四颗棋子
                            // 看一看能不能落下第五颗棋子
                            if (isForbiddenMove(board_copy, newCoordinate1, player) == NO) { // 判断第五颗棋子能否落下
                                num++;
                            }
                            board_copy[newCoordinate3.x][newCoordinate3.y] = NOBODY; // 撤销落下的第四颗棋子
                        }
                    }
                }
            }

            // 反方向的 1-0-2
            if (x + dx2 >= 0 && x + dx2 < SIZE && y + dy2 >= 0 && y + dy2 < SIZE && board_copy[x + dx2][y + dy2] == NOBODY) { // 判断是不是空位
                signed char dx_1 = dx1;
                signed char dy_1 = dy1;
                signed char dx_2 = dx2;
                signed char dy_2 = dy2;
                int count2 = 0;
                Coordinate newCoordinate1 = {x - directions[i][0], y - directions[i][1]}; // 四子连珠类型冲四的第四颗棋子
                Coordinate newCoordinate2 = {x + directions[i][0], y + directions[i][1]}; // 2-0-2 跳冲四的第四颗棋子
                Coordinate newCoordinate3 = {x - 4*directions[i][0], y - 4*directions[i][1]}; // 1-0-3 跳冲四的第四颗棋子
                // 跳过空位数二子连珠
                dx_2 -= directions[i][0];
                dy_2 -= directions[i][1];
                while (x + dx_2 >= 0 && x + dx_2 < SIZE && y + dy_2 >= 0 && y + dy_2 < SIZE && board_copy[x + dx_2][y + dy_2] == player) {
                    count2++;
                    dx_2 -= directions[i][0];
                    dy_2 -= directions[i][1];
                }
                if (count2 == 2) {
                    // 判断四子连珠的冲四
                    if (isForbiddenMove(board_copy, newCoordinate1, player) == NO) { // 判断第四颗棋子能否落下
                        int avail_five = 0; // 记录四子连珠两端能形成五连的数量
                        board_copy[newCoordinate1.x][newCoordinate1.y] = player; // 假设落下了第四颗棋子
                        
                        // 看一看正方向第五个是不是空位
                        if (x + dx_1 >= 0 && x + dx_1 < SIZE && y + dy_1 >= 0 && y + dy_1 < SIZE && board_copy[x + dx_1][y + dy_1] == NOBODY) {
                            Coordinate newCoordinate = {x + dx_1, y + dy_1};
                            // 多看一格，确保不是长连
                            dx_1 += directions[i][0];
                            dy_1 += directions[i][1];
                            if (x + dx_1 < 0 || x + dx_1 >= SIZE || y + dy_1 < 0 || y + dy_1 >= SIZE || board_copy[x + dx_1][y + dy_1] != player) {
                                if (isForbiddenMove(board_copy, newCoordinate, player) == NO) { // 判断第五颗棋子能否落下
                                    avail_five++;
                                }
                            }
                            // 撤销多看的一格
                            dx_1 -= directions[i][0];
                            dy_1 -= directions[i][1];
                        }
                        // 看一看反方向第五个是不是空位
                        if (x + dx_2 >= 0 && x + dx_2 < SIZE && y + dy_2 >= 0 && y + dy_2 < SIZE && board_copy[x + dx_2][y + dy_2] == NOBODY) {
                            Coordinate newCoordinate = {x + dx_2, y + dy_2};
                            // 多看一格，确保不是长连
                            dx_2 -= directions[i][0];
                            dy_2 -= directions[i][1];
                            if (x + dx_2 < 0 || x + dx_2 >= SIZE || y + dy_2 < 0 || y + dy_2 >= SIZE || board_copy[x + dx_2][y + dy_2] != player) {
                                if (isForbiddenMove(board_copy, newCoordinate, player) == NO) { // 判断第五颗棋子能否落下
                                    avail_five++;
                                }
                            }
                            // 撤销多看的一格
                            dx_2 += directions[i][0];
                            dy_2 += directions[i][1];
                        }
                        
                        // 判断能否形成四子连珠的冲四
                        if (avail_five == 1) {
                            num++;
                        }
                        board_copy[newCoordinate1.x][newCoordinate1.y] = NOBODY; // 撤销落下的第四颗棋子
                    }

                    // 判断 2-0-2 跳冲四
                    if (   newCoordinate2.x >= 0 && newCoordinate2.x < SIZE
                        && newCoordinate2.y >= 0 && newCoordinate2.y < SIZE
                        && board_copy[newCoordinate2.x][newCoordinate2.y] == NOBODY
                        && (   newCoordinate2.x + directions[i][0] < 0 || newCoordinate2.x + directions[i][0] >= SIZE
                            || newCoordinate2.y + directions[i][1] < 0 || newCoordinate2.y + directions[i][1] >= SIZE
                            || board_copy[newCoordinate2.x + directions[i][0]][newCoordinate2.y + directions[i][1]] != player)) { // 判断是不是空位，并同时排除可能的长连
                        if (isForbiddenMove(board_copy, newCoordinate2, player) == NO) { // 判断第四颗棋子能否落下
                            board_copy[newCoordinate2.x][newCoordinate2.y] = player; // 假设落下了第四颗棋子
                            // 看一看能不能落下第五颗棋子
                            if (isForbiddenMove(board_copy, newCoordinate1, player) == NO) { // 判断第五颗棋子能否落下
                                num++;
                            }
                            board_copy[newCoordinate2.x][newCoordinate2.y] = NOBODY; // 撤销落下的第四颗棋子
                        }
                    }

                    // 判断 1-0-3 跳冲四
                    if (   newCoordinate3.x >= 0 && newCoordinate3.x < SIZE
                        && newCoordinate3.y >= 0 && newCoordinate3.y < SIZE
                        && board_copy[newCoordinate3.x][newCoordinate3.y] == NOBODY
                        && (   newCoordinate3.x - directions[i][0] < 0 || newCoordinate3.x - directions[i][0] >= SIZE
                            || newCoordinate3.y - directions[i][1] < 0 || newCoordinate3.y - directions[i][1] >= SIZE
                            || board_copy[newCoordinate3.x + directions[i][0]][newCoordinate3.y + directions[i][1]] != player)) { // 判断是不是空位，并同时排除可能的长连
                        if (isForbiddenMove(board_copy, newCoordinate3, player) == NO) { // 判断第四颗棋子能否落下
                            board_copy[newCoordinate3.x][newCoordinate3.y] = player; // 假设落下了第四颗棋子
                            // 看一看能不能落下第五颗棋子
                            if (isForbiddenMove(board_copy, newCoordinate1, player) == NO) { // 判断第五颗棋子能否落下
                                num++;
                            }
                            board_copy[newCoordinate3.x][newCoordinate3.y] = NOBODY; // 撤销落下的第四颗棋子
                        }
                    }
                }
            }

            // 正方向的 1-0-0-2
            if (x + 4*directions[i][0] >= 0 && x + 4*directions[i][0] < SIZE && y + 4*directions[i][1] >= 0 && y + 4*directions[i][1] < SIZE) { // 判断是不是真的塞得下
                if (    board_copy[x +   directions[i][0]][y +   directions[i][1]] == NOBODY
                    &&  board_copy[x + 2*directions[i][0]][y + 2*directions[i][1]] == NOBODY
                    &&  board_copy[x + 3*directions[i][0]][y + 3*directions[i][1]] == player
                    &&  board_copy[x + 4*directions[i][0]][y + 4*directions[i][1]] == player
                    && (   x + 5*directions[i][0] < 0 || x + 5*directions[i][0] >= SIZE
                        || y + 5*directions[i][1] < 0 || y + 5*directions[i][1] >= SIZE
                        || board_copy[x + 5*directions[i][0]][y + 5*directions[i][1]] != player
                        )
                    )
                { // 判断是否为 1-0-0-2 类型，并排除长连情况
                        Coordinate newCoordinate1 = {x + directions[i][0], y + directions[i][1]};
                        Coordinate newCoordinate2 = {x + 2*directions[i][0], y + 2*directions[i][1]};
                        if (isForbiddenMove(board_copy, newCoordinate1, player) == NO) { // 判断第四颗棋子能否落在第一个空位
                            board_copy[newCoordinate1.x][newCoordinate1.y] = player; // 假设落下了第四颗棋子
                            // 看一看能不能落下第五颗棋子
                            if (isForbiddenMove(board_copy, newCoordinate2, player) == NO) { // 判断第五颗棋子能否落下
                                num++;
                            }
                            board_copy[newCoordinate1.x][newCoordinate1.y] = NOBODY; // 撤销落下的第四颗棋子
                        }
                        if (isForbiddenMove(board_copy, newCoordinate2, player) == NO) { // 判断第四颗棋子能否落在第二个空位
                            board_copy[newCoordinate2.x][newCoordinate2.y] = player; // 假设落下了第四颗棋子
                            // 看一看能不能落下第五颗棋子
                            if (isForbiddenMove(board_copy, newCoordinate1, player) == NO) { // 判断第五颗棋子能否落下
                                num++;
                            }
                            board_copy[newCoordinate2.x][newCoordinate2.y] = NOBODY; // 撤销落下的第四颗棋子
                        }
                }
            }

            // 反方向的 1-0-0-2
            if (x - 4*directions[i][0] >= 0 && x - 4*directions[i][0] < SIZE && y - 4*directions[i][1] >= 0 && y - 4*directions[i][1] < SIZE) { // 判断是不是真的塞得下
                if (   board_copy[x -   directions[i][0]][y -   directions[i][1]] == NOBODY
                    && board_copy[x - 2*directions[i][0]][y - 2*directions[i][1]] == NOBODY
                    && board_copy[x - 3*directions[i][0]][y - 3*directions[i][1]] == player
                    && board_copy[x - 4*directions[i][0]][y - 4*directions[i][1]] == player
                    && (   x - 5*directions[i][0] < 0 || x - 5*directions[i][0] >= SIZE
                        || y - 5*directions[i][1] < 0 || y - 5*directions[i][1] >= SIZE
                        || board_copy[x - 5*directions[i][0]][y - 5*directions[i][1]] != player
                        )
                    )
                { // 判断是否为 1-0-0-2 类型
                    Coordinate newCoordinate1 = {x - directions[i][0], y - directions[i][1]};
                    Coordinate newCoordinate2 = {x - 2*directions[i][0], y - 2*directions[i][1]};
                    if (isForbiddenMove(board_copy, newCoordinate1, player) == NO) { // 判断第四颗棋子能否落在第一个空位
                        board_copy[newCoordinate1.x][newCoordinate1.y] = player; // 假设落下了第四颗棋子
                        // 看一看能不能落下第五颗棋子
                        if (isForbiddenMove(board_copy, newCoordinate2, player) == NO) { // 判断第五颗棋子能否落下
                            num++;
                        }
                        board_copy[newCoordinate1.x][newCoordinate1.y] = NOBODY; // 撤销落下的第四颗棋子
                    }
                    if (isForbiddenMove(board_copy, newCoordinate2, player) == NO) { // 判断第四颗棋子能否落在第二个空位
                        board_copy[newCoordinate2.x][newCoordinate2.y] = player; // 假设落下了第四颗棋子
                        // 看一看能不能落下第五颗棋子
                        if (isForbiddenMove(board_copy, newCoordinate1, player) == NO) { // 判断第五颗棋子能否落下
                            num++;
                        }
                        board_copy[newCoordinate2.x][newCoordinate2.y] = NOBODY; // 撤销落下的第四颗棋子
                    }
                }
            }

            // 正方向的 1-0-1-0-1
            if (x + 4*directions[i][0] >= 0 && x + 4*directions[i][0] < SIZE && y + 4*directions[i][1] >= 0 && y + 4*directions[i][1] < SIZE) { // 判断是不是真的塞得下
                if (   board_copy[x +   directions[i][0]][y +   directions[i][1]] == NOBODY
                    && board_copy[x + 2*directions[i][0]][y + 2*directions[i][1]] == player
                    && board_copy[x + 3*directions[i][0]][y + 3*directions[i][1]] == NOBODY
                    && board_copy[x + 4*directions[i][0]][y + 4*directions[i][1]] == player
                    && (    x + 5*directions[i][0] < 0 || x + 5*directions[i][0] >= SIZE
                        ||  y + 5*directions[i][1] < 0 || y + 5*directions[i][1] >= SIZE
                        ||  board_copy[x + 5*directions[i][0]][y + 5*directions[i][1]] != player
                        )
                    )
                { // 判断是否为 1-0-1-0-1 类型，并排除长连情况
                        Coordinate newCoordinate1 = {x + directions[i][0], y + directions[i][1]};
                        Coordinate newCoordinate2 = {x + 3*directions[i][0], y + 3*directions[i][1]};
                        if (isForbiddenMove(board_copy, newCoordinate1, player) == NO) { // 判断第四颗棋子能否落在第一个空位
                            board_copy[newCoordinate1.x][newCoordinate1.y] = player; // 假设落下了第四颗棋子
                            // 看一看能不能落下第五颗棋子
                            if (isForbiddenMove(board_copy, newCoordinate2, player) == NO) { // 判断第五颗棋子能否落下
                                num++;
                            }
                            board_copy[newCoordinate1.x][newCoordinate1.y] = NOBODY; // 撤销落下的第四颗棋子
                        }
                        if (isForbiddenMove(board_copy, newCoordinate2, player) == NO) { // 判断第四颗棋子能否落在第二个空位
                            board_copy[newCoordinate2.x][newCoordinate2.y] = player; // 假设落下了第四颗棋子
                            // 看一看能不能落下第五颗棋子
                            if (isForbiddenMove(board_copy, newCoordinate1, player) == NO) { // 判断第五颗棋子能否落下
                                num++;
                            }
                            board_copy[newCoordinate2.x][newCoordinate2.y] = NOBODY; // 撤销落下的第四颗棋子
                        }
                }
            }

            // 反方向的 1-0-1-0-1
            if (x - 4*directions[i][0] >= 0 && x - 4*directions[i][0] < SIZE && y - 4*directions[i][1] >= 0 && y - 4*directions[i][1] < SIZE) { // 判断是不是真的塞得下
                if (   board_copy[x -   directions[i][0]][y -   directions[i][1]] == NOBODY
                    && board_copy[x - 2*directions[i][0]][y - 2*directions[i][1]] == player
                    && board_copy[x - 3*directions[i][0]][y - 3*directions[i][1]] == NOBODY
                    && board_copy[x - 4*directions[i][0]][y - 4*directions[i][1]] == player
                    && (   x - 5*directions[i][0] < 0 || x - 5*directions[i][0] >= SIZE
                        || y - 5*directions[i][1] < 0 || y - 5*directions[i][1] >= SIZE
                        || board_copy[x - 5*directions[i][0]][y - 5*directions[i][1]] != player
                        )
                    )
                { // 判断是否为 1-0-1-0-1 类型，并排除长连情况
                        Coordinate newCoordinate1 = {x - directions[i][0], y - directions[i][1]};
                        Coordinate newCoordinate2 = {x - 3*directions[i][0], y - 3*directions[i][1]};
                        if (isForbiddenMove(board_copy, newCoordinate1, player) == NO) { // 判断第四颗棋子能否落在第一个空位
                            board_copy[newCoordinate1.x][newCoordinate1.y] = player; // 假设落下了第四颗棋子
                            // 看一看能不能落下第五颗棋子
                            if (isForbiddenMove(board_copy, newCoordinate2, player) == NO) { // 判断第五颗棋子能否落下
                                num++;
                            }
                            board_copy[newCoordinate1.x][newCoordinate1.y] = NOBODY; // 撤销落下的第四颗棋子
                        }
                        if (isForbiddenMove(board_copy, newCoordinate2, player) == NO) { // 判断第四颗棋子能否落在第二个空位
                            board_copy[newCoordinate2.x][newCoordinate2.y] = player; // 假设落下了第四颗棋子
                            // 看一看能不能落下第五颗棋子
                            if (isForbiddenMove(board_copy, newCoordinate1, player) == NO) { // 判断第五颗棋子能否落下
                                num++;
                            }
                            board_copy[newCoordinate2.x][newCoordinate2.y] = NOBODY; // 撤销落下的第四颗棋子
                        }
                }
            }

            // 1-0-1-0-1 类型（1 在中央）
            if (   x + 2*directions[i][0] >= 0 && x + 2*directions[i][0] < SIZE && y + 2*directions[i][1] >= 0 && y + 2*directions[i][1] < SIZE
                && x - 2*directions[i][0] >= 0 && x - 2*directions[i][0] < SIZE && y - 2*directions[i][1] >= 0 && y - 2*directions[i][1] < SIZE) { // 判断是不是真的塞得下
                if (   board_copy[x + directions[i][0]][y + directions[i][1]] == NOBODY
                    && board_copy[x - directions[i][0]][y - directions[i][1]] == NOBODY
                    && board_copy[x + 2*directions[i][0]][y + 2*directions[i][1]] == player
                    && board_copy[x - 2*directions[i][0]][y - 2*directions[i][1]] == player
                    && (   x + 3*directions[i][0] < 0 || x + 3*directions[i][0] >= SIZE
                        || y + 3*directions[i][1] < 0 || y + 3*directions[i][1] >= SIZE
                        || board_copy[x + 3*directions[i][0]][y + 3*directions[i][1]] != player
                        )
                    && (   x - 3*directions[i][0] < 0 || x - 3*directions[i][0] >= SIZE
                        || y - 3*directions[i][1] < 0 || y - 3*directions[i][1] >= SIZE
                        || board_copy[x - 3*directions[i][0]][y - 3*directions[i][1]] != player
                        )
                    )
                { // 判断是否为 1-0-1-0-1 类型，并排除长连情况
                        Coordinate newCoordinate1 = {x + directions[i][0], y + directions[i][1]};
                        Coordinate newCoordinate2 = {x - directions[i][0], y - directions[i][1]};
                        if (isForbiddenMove(board_copy, newCoordinate1, player) == NO) { // 判断第四颗棋子能否落在第一个空位
                            board_copy[newCoordinate1.x][newCoordinate1.y] = player; // 假设落下了第四颗棋子
                            // 看一看能不能落下第五颗棋子
                            if (isForbiddenMove(board_copy, newCoordinate2, player) == NO) { // 判断第五颗棋子能否落下
                                num++;
                            }
                            board_copy[newCoordinate1.x][newCoordinate1.y] = NOBODY; // 撤销落下的第四颗棋子
                        }
                        if (isForbiddenMove(board_copy, newCoordinate2, player) == NO) { // 判断第四颗棋子能否落在第二个空位
                            board_copy[newCoordinate2.x][newCoordinate2.y] = player; // 假设落下了第四颗棋子
                            // 看一看能不能落下第五颗棋子
                            if (isForbiddenMove(board_copy, newCoordinate1, player) == NO) { // 判断第五颗棋子能否落下
                                num++;
                            }
                            board_copy[newCoordinate2.x][newCoordinate2.y] = NOBODY; // 撤销落下的第四颗棋子
                        }
                }
            }

        } else if (count == 2) {
        // 2-0-1 类型，可能在两个相反方向上形成不同的眠三，每个眠三有三种成冲四方式
        // 2-0-0-1 类型，可能在两个相反方向上形成不同的眠三，每个眠三有两种成冲四方式

            // 正方向的 2-0-1
            if (x + dx1 >= 0 && x + dx1 < SIZE && y + dy1 >= 0 && y + dy1 < SIZE && board_copy[x + dx1][y + dy1] == NOBODY) { // 判断是不是空位
                signed char dx_1 = dx1;
                signed char dy_1 = dy1;
                signed char dx_2 = dx2;
                signed char dy_2 = dy2;
                int count2 = 0;
                Coordinate newCoordinate1 = {x + dx_1, y + dy_1}; // 四子连珠类型冲四的第四颗棋子
                Coordinate newCoordinate2 = {x + dx_1 + 2*directions[i][0], y + dy_1 + 2*directions[i][1]}; // 2-0-2 跳冲四的第四颗棋子
                Coordinate newCoordinate3 = {x + dx_2, y + dy_2}; // 3-0-1 跳冲四的第四颗棋子
                // 跳过空位数一子
                dx_1 += directions[i][0];
                dy_1 += directions[i][1];
                while (x + dx_1 >= 0 && x + dx_1 < SIZE && y + dy_1 >= 0 && y + dy_1 < SIZE && board_copy[x + dx_1][y + dy_1] == player) {
                    count2++;
                    dx_1 += directions[i][0];
                    dy_1 += directions[i][1];
                }
                if (count2 == 1) {
                    // 判断四子连珠的冲四
                    if (isForbiddenMove(board_copy, newCoordinate1, player) == NO) { // 判断第四颗棋子能否落下
                        int avail_five = 0; // 记录四子连珠两端能形成五连的数量
                        board_copy[newCoordinate1.x][newCoordinate1.y] = player; // 假设落下了第四颗棋子
                        // 看一看正方向第五个是不是空位，并排除长连
                        if (    x + dx_1 >= 0 && x + dx_1 < SIZE && y + dy_1 >= 0 && y + dy_1 < SIZE && board_copy[x + dx_1][y + dy_1] == NOBODY
                            && (   x + dx_1 + directions[i][0] < 0 || x + dx_1 + directions[i][0] >= SIZE
                                || y + dy_1 + directions[i][1] < 0 || y + dy_1 + directions[i][1] >= SIZE
                                || board_copy[x + dx_1 + directions[i][0]][y + dy_1 + directions[i][1]] != player
                                )
                            )
                        {
                            Coordinate newCoordinate = {x + dx_1, y + dy_1};
                            if (isForbiddenMove(board_copy, newCoordinate, player) == NO) { // 判断第五颗棋子能否落下
                                avail_five++;
                            }
                        }
                        // 看一看反方向第五个是不是空位，并排除长连
                        if (x + dx_2 >= 0 && x + dx_2 < SIZE && y + dy_2 >= 0 && y + dy_2 < SIZE && board_copy[x + dx_2][y + dy_2] == NOBODY
                            && (   x + dx_2 - directions[i][0] < 0 || x + dx_2 - directions[i][0] >= SIZE
                                || y + dy_2 - directions[i][1] < 0 || y + dy_2 - directions[i][1] >= SIZE
                                || board_copy[x + dx_2 - directions[i][0]][y + dy_2 - directions[i][1]] != player
                                )
                            )
                        {
                            Coordinate newCoordinate = {x + dx_2, y + dy_2};
                            if (isForbiddenMove(board_copy, newCoordinate, player) == NO) { // 判断第五颗棋子能否落下
                                avail_five++;
                            }
                        }
                        
                        // 判断能否形成四子连珠的冲四
                        if (avail_five == 1) {
                            num++;
                        }
                        board_copy[newCoordinate1.x][newCoordinate1.y] = NOBODY; // 撤销落下的第四颗棋子
                    }

                    // 判断 2-0-2 跳冲四
                    if (    newCoordinate2.x >= 0 && newCoordinate2.x < SIZE && newCoordinate2.y >= 0 && newCoordinate2.y < SIZE && board_copy[newCoordinate2.x][newCoordinate2.y] == NOBODY
                        && (
                                newCoordinate2.x + directions[i][0] < 0 || newCoordinate2.x + directions[i][0] >= SIZE
                            ||  newCoordinate2.y + directions[i][1] < 0 || newCoordinate2.y + directions[i][1] >= SIZE
                            ||  board_copy[newCoordinate2.x + directions[i][0]][newCoordinate2.y + directions[i][1]] != player
                            )
                        )
                    { // 判断是不是空位，并同时排除可能的长连
                        if (isForbiddenMove(board_copy, newCoordinate2, player) == NO) { // 判断第四颗棋子能否落下
                            board_copy[newCoordinate2.x][newCoordinate2.y] = player; // 假设落下了第四颗棋子
                            // 看一看能不能落下第五颗棋子
                            if (isForbiddenMove(board_copy, newCoordinate1, player) == NO) { // 判断第五颗棋子能否落下
                                num++;
                            }
                            board_copy[newCoordinate2.x][newCoordinate2.y] = NOBODY; // 撤销落下的第四颗棋子
                        }
                    }

                    // 判断 3-0-1 跳冲四
                    if (    newCoordinate3.x >= 0 && newCoordinate3.x < SIZE && newCoordinate3.y >= 0 && newCoordinate3.y < SIZE && board_copy[newCoordinate3.x][newCoordinate3.y] == NOBODY
                        && (
                                newCoordinate3.x - directions[i][0] < 0 || newCoordinate3.x - directions[i][0] >= SIZE
                            ||  newCoordinate3.y - directions[i][1] < 0 || newCoordinate3.y - directions[i][1] >= SIZE
                            ||  board_copy[newCoordinate3.x - directions[i][0]][newCoordinate3.y - directions[i][1]] != player
                            )
                        )
                    { // 判断是不是空位，并同时排除可能的长连
                        if (isForbiddenMove(board_copy, newCoordinate3, player) == NO) { // 判断第四颗棋子能否落下
                            board_copy[newCoordinate3.x][newCoordinate3.y] = player; // 假设落下了第四颗棋子
                           // 看一看能不能落下第五颗棋子
                            if (isForbiddenMove(board_copy, newCoordinate1, player) == NO) { // 判断第五颗棋子能否落下
                                num++;
                            }
                            board_copy[newCoordinate3.x][newCoordinate3.y] = NOBODY; // 撤销落下的第四颗棋子
                        }
                    }
                }
            }

            // 反方向的 2-0-1
            if (x + dx2 >= 0 && x + dx2 < SIZE && y + dy2 >= 0 && y + dy2 < SIZE && board_copy[x + dx2][y + dy2] == NOBODY) { // 判断是不是空位
                signed char dx_1 = dx1;
                signed char dy_1 = dy1;
                signed char dx_2 = dx2;
                signed char dy_2 = dy2;
                int count2 = 0;
                Coordinate newCoordinate1 = {x + dx_2, y + dy_2}; // 四子连珠类型冲四的第四颗棋子
                Coordinate newCoordinate2 = {x + dx_2 - 2*directions[i][0], y + dy_2 - 2*directions[i][1]}; // 2-0-2 跳冲四的第四颗棋子
                Coordinate newCoordinate3 = {x + dx_1, y + dy_1}; // 3-0-1 跳冲四的第四颗棋子
                // 跳过空位数一子
                dx_2 -= directions[i][0];
                dy_2 -= directions[i][1];
                while (x + dx_2 >= 0 && x + dx_2 < SIZE && y + dy_2 >= 0 && y + dy_2 < SIZE && board_copy[x + dx_2][y + dy_2] == player) {
                    count2++;
                    dx_2 -= directions[i][0];
                    dy_2 -= directions[i][1];
                }
                if (count2 == 1) {
                    // 判断四子连珠的冲四
                    if (isForbiddenMove(board_copy, newCoordinate1, player) == NO) { // 判断第四颗棋子能否落下
                        int avail_five = 0; // 记录四子连珠两端能形成五连的数量
                        board_copy[newCoordinate1.x][newCoordinate1.y] = player; // 假设落下了第四颗棋子

                        // 看一看正方向第五个是不是空位，并排除长连
                        if (    x + dx_1 >= 0 && x + dx_1 < SIZE && y + dy_1 >= 0 && y + dy_1 < SIZE && board_copy[x + dx_1][y + dy_1] == NOBODY
                            && (   x + dx_1 + directions[i][0] < 0 || x + dx_1 + directions[i][0] >= SIZE
                                || y + dy_1 + directions[i][1] < 0 || y + dy_1 + directions[i][1] >= SIZE
                                || board_copy[x + dx_1 + directions[i][0]][y + dy_1 + directions[i][1]] != player
                                )
                            )
                        {
                            Coordinate newCoordinate = {x + dx_1, y + dy_1};
                            if (isForbiddenMove(board_copy, newCoordinate, player) == NO) { // 判断第五颗棋子能否落下
                                avail_five++;
                            }
                        }
                        // 看一看反方向第五个是不是空位，并排除长连
                        if (x + dx_2 >= 0 && x + dx_2 < SIZE && y + dy_2 >= 0 && y + dy_2 < SIZE && board_copy[x + dx_2][y + dy_2] == NOBODY
                            && (   x + dx_2 - directions[i][0] < 0 || x + dx_2 - directions[i][0] >= SIZE
                                || y + dy_2 - directions[i][1] < 0 || y + dy_2 - directions[i][1] >= SIZE
                                || board_copy[x + dx_2 - directions[i][0]][y + dy_2 - directions[i][1]] != player
                                )
                            )
                        {
                            Coordinate newCoordinate = {x + dx_2, y + dy_2};
                            if (isForbiddenMove(board_copy, newCoordinate, player) == NO) { // 判断第五颗棋子能否落下
                                avail_five++;
                            }
                        }
                        
                        // 判断能否形成四子连珠的冲四
                        if (avail_five == 1) {
                            num++;
                        }
                        board_copy[newCoordinate1.x][newCoordinate1.y] = NOBODY; // 撤销落下的第四颗棋子
                    }

                    // 判断 2-0-2 跳冲四
                    if (    newCoordinate2.x >= 0 && newCoordinate2.x < SIZE && newCoordinate2.y >= 0 && newCoordinate2.y < SIZE && board_copy[newCoordinate2.x][newCoordinate2.y] == NOBODY
                        && (    newCoordinate2.x - directions[i][0] < 0 || newCoordinate2.x - directions[i][0] >= SIZE
                            ||  newCoordinate2.y - directions[i][1] < 0 || newCoordinate2.y - directions[i][1] >= SIZE
                            ||  board_copy[newCoordinate2.x - directions[i][0]][newCoordinate2.y - directions[i][1]] != player
                            )
                        )
                    { // 判断是不是空位，并同时排除可能的长连
                        if (isForbiddenMove(board_copy, newCoordinate2, player) == NO) { // 判断第四颗棋子能否落下
                            board_copy[newCoordinate2.x][newCoordinate2.y] = player; // 假设落下了第四颗棋子
                           // 看一看能不能落下第五颗棋子
                            if (isForbiddenMove(board_copy, newCoordinate1, player) == NO) { // 判断第五颗棋子能否落下
                                num++;
                            }
                            board_copy[newCoordinate2.x][newCoordinate2.y] = NOBODY; // 撤销落下的第四颗棋子
                        }
                    }

                    // 判断 3-0-1 跳冲四
                    if (    newCoordinate3.x >= 0 && newCoordinate3.x < SIZE && newCoordinate3.y >= 0 && newCoordinate3.y < SIZE && board_copy[newCoordinate3.x][newCoordinate3.y] == NOBODY
                        && (    newCoordinate3.x + directions[i][0] < 0 || newCoordinate3.x + directions[i][0] >= SIZE
                            ||  newCoordinate3.y + directions[i][1] < 0 || newCoordinate3.y + directions[i][1] >= SIZE
                            ||  board_copy[newCoordinate3.x + directions[i][0]][newCoordinate3.y + directions[i][1]] != player
                            )
                        )
                    { // 判断是不是空位，并同时排除可能的长连
                        if (isForbiddenMove(board_copy, newCoordinate3, player) == NO) { // 判断第四颗棋子能否落下
                            board_copy[newCoordinate3.x][newCoordinate3.y] = player; // 假设落下了第四颗棋子
                            // 看一看能不能落下第五颗棋子
                            if (isForbiddenMove(board_copy, newCoordinate1, player) == NO) { // 判断第五颗棋子能否落下
                                num++;
                            }
                            board_copy[newCoordinate3.x][newCoordinate3.y] = NOBODY; // 撤销落下的第四颗棋子
                        }
                    }
                }
            }

            // 正方向的 2-0-0-1
            if (x + dx1 + 2*directions[i][0] >= 0 && x + dx1 + 2*directions[i][0] < SIZE && y + dy1 + 2*directions[i][1] >= 0 && y + dy1 + 2*directions[i][1] < SIZE) { // 判断是不是真的塞得下，并排除长连
                if (   board_copy[x + dx1                     ][y + dy1                     ] == NOBODY
                    && board_copy[x + dx1 +   directions[i][0]][y + dy1 +   directions[i][1]] == NOBODY
                    && board_copy[x + dx1 + 2*directions[i][0]][y + dy1 + 2*directions[i][1]] == player
                    && (    x + dx1 + 3*directions[i][0] < 0 || x + dx1 + 3*directions[i][0] >= SIZE
                        ||  y + dy1 + 3*directions[i][1] < 0 || y + dy1 + 3*directions[i][1] >= SIZE
                        ||  board_copy[x + dx1 + 3*directions[i][0]][y + dy1 + 3*directions[i][1]] != player
                        )
                    )
                { // 判断是否为 2-0-0-1 类型
                        Coordinate newCoordinate1 = {x + dx1, y + dy1};
                        Coordinate newCoordinate2 = {x + dx1 + directions[i][0], y + dy1 + directions[i][1]};
                        if (isForbiddenMove(board_copy, newCoordinate1, player) == NO) { // 判断第四颗棋子能否落在第一个空位
                            board_copy[newCoordinate1.x][newCoordinate1.y] = player; // 假设落下了第四颗棋子
                            // 看一看能不能落下第五颗棋子
                            if (isForbiddenMove(board_copy, newCoordinate2, player) == NO) { // 判断第五颗棋子能否落下
                                num++;
                            }
                            board_copy[newCoordinate1.x][newCoordinate1.y] = NOBODY; // 撤销落下的第四颗棋子
                        }
                        if (isForbiddenMove(board_copy, newCoordinate2, player) == NO) { // 判断第四颗棋子能否落在第二个空位
                            board_copy[newCoordinate2.x][newCoordinate2.y] = player; // 假设落下了第四颗棋子
                            // 看一看能不能落下第五颗棋子
                            if (isForbiddenMove(board_copy, newCoordinate1, player) == NO) { // 判断第五颗棋子能否落下
                                num++;
                            }
                            board_copy[newCoordinate2.x][newCoordinate2.y] = NOBODY; // 撤销落下的第四颗棋子
                        }
                }
            }

            // 反方向的 2-0-0-1
            if (x + dx2 - 2*directions[i][0] >= 0 && x + dx2 - 2*directions[i][0] < SIZE && y + dy2 - 2*directions[i][1] >= 0 && y + dy2 - 2*directions[i][1] < SIZE) { // 判断是不是真的塞得下，并排除长连
                if (   board_copy[x + dx2                    ][y + dy2                      ] == NOBODY
                    && board_copy[x + dx2 - directions[i ][0]][y + dy2 -    directions[i][1]] == NOBODY
                    && board_copy[x + dx2 - 2*directions[i][0]][y + dy2 - 2*directions[i][1]] == player
                    && (    x + dx2 - 3*directions[i][0] < 0 || x + dx2 - 3*directions[i][0] >= SIZE
                        ||  y + dy2 - 3*directions[i][1] < 0 || y + dy2 - 3*directions[i][1] >= SIZE
                        ||  board_copy[x + dx2 - 3*directions[i][0]][y + dy2 - 3*directions[i][1]] != player
                        )
                    )
                { // 判断是否为 2-0-0-1 类型
                        Coordinate newCoordinate1 = {x + dx2, y + dy2};
                        Coordinate newCoordinate2 = {x + dx2 - directions[i][0], y + dy2 - directions[i][1]};
                        if (isForbiddenMove(board_copy, newCoordinate1, player) == NO) { // 判断第四颗棋子能否落在第一个空位
                            board_copy[newCoordinate1.x][newCoordinate1.y] = player; // 假设落下了第四颗棋子
                            // 看一看能不能落下第五颗棋子
                            if (isForbiddenMove(board_copy, newCoordinate2, player) == NO) { // 判断第五颗棋子能否落下
                                num++;
                            }
                            board_copy[newCoordinate1.x][newCoordinate1.y] = NOBODY; // 撤销落下的第四颗棋子
                        }
                        if (isForbiddenMove(board_copy, newCoordinate2, player) == NO) { // 判断第四颗棋子能否落在第二个空位
                            board_copy[newCoordinate2.x][newCoordinate2.y] = player; // 假设落下了第四颗棋子
                            // 看一看能不能落下第五颗棋子
                            if (isForbiddenMove(board_copy, newCoordinate1, player) == NO) { // 判断第五颗棋子能否落下
                                num++;
                            }
                            board_copy[newCoordinate2.x][newCoordinate2.y] = NOBODY; // 撤销落下的第四颗棋子
                        }
                }
            }
        }
    }
    return num;
}
