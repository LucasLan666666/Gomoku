// 此文件用于对活三的判断，专门为打分设计
#include "gomoku.h"

// 判断活三，返回能形成活四的数量
int threeForWin(int board[SIZE][SIZE], struct placeStone coordinate, int player){
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

        // 三子连珠类型，可能在两个方向形成四子连珠，为了判断四子连珠是不是活四，又要验证两端能否成五
        if (count == 3){
            // 判断两端是否能落子
            int avail_straightFour = 0; // 记录两端能先形成活四的数量

            // 先看正方向一端能否落子形成四子连珠
            if (x + dx1 >= 0 && x + dx1 < SIZE && y + dy1 >= 0 && y + dy1 < SIZE && board_copy[x + dx1][y + dy1] == NOBODY){
                int dx_1 = dx1;
                int dy_1 = dy1;
                int dx_2 = dx2;
                int dy_2 = dy2;
                struct placeStone newCoordinate = {x + dx_1, y + dy_1};
                if (isForbiddenMove(board_copy, newCoordinate, player) == NO){ // 判断第四颗棋子能否落下
                    int avail_five = 0; // 记录四子连珠两端能形成五连的数量
                    board_copy[newCoordinate.x][newCoordinate.y] = player; // 假设落下了第四颗棋子
                    // 正方向多看一格
                    dx_1 += directions[i][0];
                    dy_1 += directions[i][1];

                    // 看一看正方向第五个是不是空位
                    if (x + dx_1 >= 0 && x + dx_1 < SIZE && y + dy_1 >= 0 && y + dy_1 < SIZE && board_copy[x + dx_1][y + dy_1] == NOBODY){
                        struct placeStone newCoordinate = {x + dx_1, y + dy_1};
                        // 多看一格，确保不是长连
                        dx_1 += directions[i][0];
                        dy_1 += directions[i][1];
                        if (x + dx_1 < 0 || x + dx_1 >= SIZE || y + dy_1 < 0 || y + dy_1 >= SIZE || board_copy[x + dx_1][y + dy_1] != player){                      
                            if (isForbiddenMove(board_copy, newCoordinate, player) == NO){ // 判断第五颗棋子能否落下
                                avail_five++;
                            }
                        }
                        // 撤销多看的一格
                        dx_1 -= directions[i][0];
                        dy_1 -= directions[i][1];
                    }
                    // 看一看反方向第五个是不是空位
                    if (x + dx_2 >= 0 && x + dx_2 < SIZE && y + dy_2 >= 0 && y + dy_2 < SIZE && board_copy[x + dx_2][y + dy_2] == NOBODY){
                        struct placeStone newCoordinate = {x + dx_2, y + dy_2};
                        // 多看一格，确保不是长连
                        dx_2 -= directions[i][0];
                        dy_2 -= directions[i][1];
                        if (x + dx_2 < 0 || x + dx_2 >= SIZE || y + dy_2 < 0 || y + dy_2 >= SIZE || board_copy[x + dx_2][y + dy_2] != player){  
                            if (isForbiddenMove(board_copy, newCoordinate, player) == NO){ // 判断第五颗棋子能否落下
                                avail_five++;
                            }
                        }
                        // 撤销多看的一格
                        dx_2 += directions[i][0];
                        dy_2 += directions[i][1];
                    }

                    // 判断正方向这个四子连珠是不是活四，是的话 avail_straightFour 加一
                    if (avail_five == 2){
                        avail_straightFour++;
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
                if (isForbiddenMove(board_copy, newCoordinate, player) == NO){ // 判断第四颗棋子能否落下
                    int avail_five = 0; // 记录四子连珠两端能形成五连的数量
                    board_copy[newCoordinate.x][newCoordinate.y] = player; // 假设落下了第四颗棋子
                    // 反方向多看一格
                    dx_2 -= directions[i][0];
                    dy_2 -= directions[i][1];

                    // 看一看正方向第五个是不是空位
                    if (x + dx_1 >= 0 && x + dx_1 < SIZE && y + dy_1 >= 0 && y + dy_1 < SIZE && board_copy[x + dx_1][y + dy_1] == NOBODY){
                        struct placeStone newCoordinate = {x + dx_1, y + dy_1};
                        // 多看一格，确保不是长连
                        dx_1 += directions[i][0];
                        dy_1 += directions[i][1];
                        if (x + dx_1 < 0 || x + dx_1 >= SIZE || y + dy_1 < 0 || y + dy_1 >= SIZE || board_copy[x + dx_1][y + dy_1] != player){                      
                            if (isForbiddenMove(board_copy, newCoordinate, player) == NO){ // 判断第五颗棋子能否落下
                                avail_five++;
                            }
                        }
                        // 撤销多看的一格
                        dx_1 -= directions[i][0];
                        dy_1 -= directions[i][1];
                    }
                    // 看一看反方向第五个是不是空位
                    if (x + dx_2 >= 0 && x + dx_2 < SIZE && y + dy_2 >= 0 && y + dy_2 < SIZE && board_copy[x + dx_2][y + dy_2] == NOBODY){
                        struct placeStone newCoordinate = {x + dx_2, y + dy_2};
                        // 多看一格，确保不是长连
                        dx_2 -= directions[i][0];
                        dy_2 -= directions[i][1];
                        if (x + dx_2 < 0 || x + dx_2 >= SIZE || y + dy_2 < 0 || y + dy_2 >= SIZE || board_copy[x + dx_2][y + dy_2] != player){  
                            if (isForbiddenMove(board_copy, newCoordinate, player) == NO){ // 判断第五颗棋子能否落下
                                avail_five++;
                            }
                        }
                        // 撤销多看的一格
                        dx_2 += directions[i][0];
                        dy_2 += directions[i][1];
                    }

                    // 判断正方向这个四子连珠是不是活四，是的话 avail_straightFour 加一
                    if (avail_five == 2){
                        avail_straightFour++;
                    }
                    board_copy[newCoordinate.x][newCoordinate.y] = NOBODY; // 撤销落下的第四颗棋子
                }
            }

            num += avail_straightFour;

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
                while (x + dx_1 >= 0 && x + dx_1 < SIZE && y + dy_1 >= 0 && y + dy_1 < SIZE && board_copy[x + dx_1][y + dy_1] == player){
                    count2++;
                    dx_1 += directions[i][0];
                    dy_1 += directions[i][1];
                }
                if (count2 == 2){
                    if (isForbiddenMove(board_copy, newCoordinate, player) == NO){ // 判断第四颗棋子能否落下
                        int avail_five = 0; // 记录四子连珠两端能形成五连的数量
                        board_copy[newCoordinate.x][newCoordinate.y] = player; // 假设落下了第四颗棋子

                        // 看一看正方向第五个是不是空位
                        if (x + dx_1 >= 0 && x + dx_1 < SIZE && y + dy_1 >= 0 && y + dy_1 < SIZE && board_copy[x + dx_1][y + dy_1] == NOBODY){
                            struct placeStone newCoordinate = {x + dx_1, y + dy_1};
                            // 多看一格，确保不是长连
                            dx_1 += directions[i][0];
                            dy_1 += directions[i][1];
                            if (x + dx_1 < 0 || x + dx_1 >= SIZE || y + dy_1 < 0 || y + dy_1 >= SIZE || board_copy[x + dx_1][y + dy_1] != player){                      
                                if (isForbiddenMove(board_copy, newCoordinate, player) == NO){ // 判断第五颗棋子能否落下
                                    avail_five++;
                                }
                            }
                            // 撤销多看的一格
                            dx_1 -= directions[i][0];
                            dy_1 -= directions[i][1];
                        }
                        // 看一看反方向第五个是不是空位
                        if (x + dx_2 >= 0 && x + dx_2 < SIZE && y + dy_2 >= 0 && y + dy_2 < SIZE && board_copy[x + dx_2][y + dy_2] == NOBODY){
                            struct placeStone newCoordinate = {x + dx_2, y + dy_2};
                            // 多看一格，确保不是长连
                            dx_2 -= directions[i][0];
                            dy_2 -= directions[i][1];
                            if (x + dx_2 < 0 || x + dx_2 >= SIZE || y + dy_2 < 0 || y + dy_2 >= SIZE || board_copy[x + dx_2][y + dy_2] != player){  
                                if (isForbiddenMove(board_copy, newCoordinate, player) == NO){ // 判断第五颗棋子能否落下
                                    avail_five++;
                                }
                            }
                            // 撤销多看的一格
                            dx_2 += directions[i][0];
                            dy_2 += directions[i][1];
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
                while (x + dx_2 >= 0 && x + dx_2 < SIZE && y + dy_2 >= 0 && y + dy_2 < SIZE && board_copy[x + dx_2][y + dy_2] == player){
                    count2++;
                    dx_2 -= directions[i][0];
                    dy_2 -= directions[i][1];
                }
                if (count2 == 2){
                    if (isForbiddenMove(board_copy, newCoordinate, player) == NO){ // 判断第四颗棋子能否落下
                        int avail_five = 0; // 记录四子连珠两端能形成五连的数量
                        board_copy[newCoordinate.x][newCoordinate.y] = player; // 假设落下了第四颗棋子

                        // 看一看正方向第五个是不是空位
                        if (x + dx_1 >= 0 && x + dx_1 < SIZE && y + dy_1 >= 0 && y + dy_1 < SIZE && board_copy[x + dx_1][y + dy_1] == NOBODY){
                            struct placeStone newCoordinate = {x + dx_1, y + dy_1};
                            // 多看一格，确保不是长连
                            dx_1 += directions[i][0];
                            dy_1 += directions[i][1];
                            if (x + dx_1 < 0 || x + dx_1 >= SIZE || y + dy_1 < 0 || y + dy_1 >= SIZE || board_copy[x + dx_1][y + dy_1] != player){                      
                                if (isForbiddenMove(board_copy, newCoordinate, player) == NO){ // 判断第五颗棋子能否落下
                                    avail_five++;
                                }
                            }
                            // 撤销多看的一格
                            dx_1 -= directions[i][0];
                            dy_1 -= directions[i][1];
                        }
                        // 看一看反方向第五个是不是空位
                        if (x + dx_2 >= 0 && x + dx_2 < SIZE && y + dy_2 >= 0 && y + dy_2 < SIZE && board_copy[x + dx_2][y + dy_2] == NOBODY){
                            struct placeStone newCoordinate = {x + dx_2, y + dy_2};
                            // 多看一格，确保不是长连
                            dx_2 -= directions[i][0];
                            dy_2 -= directions[i][1];
                            if (x + dx_2 < 0 || x + dx_2 >= SIZE || y + dy_2 < 0 || y + dy_2 >= SIZE || board_copy[x + dx_2][y + dy_2] != player){  
                                if (isForbiddenMove(board_copy, newCoordinate, player) == NO){ // 判断第五颗棋子能否落下
                                    avail_five++;
                                }
                            }
                            // 撤销多看的一格
                            dx_2 += directions[i][0];
                            dy_2 += directions[i][1];
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
                while (x + dx_1 >= 0 && x + dx_1 < SIZE && y + dy_1 >= 0 && y + dy_1 < SIZE && board_copy[x + dx_1][y + dy_1] == player){
                    count2++;
                    dx_1 += directions[i][0];
                    dy_1 += directions[i][1];
                }
                if (count2 == 1){
                    if (isForbiddenMove(board_copy, newCoordinate, player) == NO){ // 判断第四颗棋子能否落下
                        int avail_five = 0; // 记录四子连珠两端能形成五连的数量
                        board_copy[newCoordinate.x][newCoordinate.y] = player; // 假设落下了第四颗棋子
                        
                        // 看一看正方向第五个是不是空位
                        if (x + dx_1 >= 0 && x + dx_1 < SIZE && y + dy_1 >= 0 && y + dy_1 < SIZE && board_copy[x + dx_1][y + dy_1] == NOBODY){
                            struct placeStone newCoordinate = {x + dx_1, y + dy_1};
                            // 多看一格，确保不是长连
                            dx_1 += directions[i][0];
                            dy_1 += directions[i][1];
                            if (x + dx_1 < 0 || x + dx_1 >= SIZE || y + dy_1 < 0 || y + dy_1 >= SIZE || board_copy[x + dx_1][y + dy_1] != player){                      
                                if (isForbiddenMove(board_copy, newCoordinate, player) == NO){ // 判断第五颗棋子能否落下
                                    avail_five++;
                                }
                            }
                            // 撤销多看的一格
                            dx_1 -= directions[i][0];
                            dy_1 -= directions[i][1];
                        }
                        // 看一看反方向第五个是不是空位
                        if (x + dx_2 >= 0 && x + dx_2 < SIZE && y + dy_2 >= 0 && y + dy_2 < SIZE && board_copy[x + dx_2][y + dy_2] == NOBODY){
                            struct placeStone newCoordinate = {x + dx_2, y + dy_2};
                            // 多看一格，确保不是长连
                            dx_2 -= directions[i][0];
                            dy_2 -= directions[i][1];
                            if (x + dx_2 < 0 || x + dx_2 >= SIZE || y + dy_2 < 0 || y + dy_2 >= SIZE || board_copy[x + dx_2][y + dy_2] != player){  
                                if (isForbiddenMove(board_copy, newCoordinate, player) == NO){ // 判断第五颗棋子能否落下
                                    avail_five++;
                                }
                            }
                            // 撤销多看的一格
                            dx_2 += directions[i][0];
                            dy_2 += directions[i][1];
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
                while (x + dx_2 >= 0 && x + dx_2 < SIZE && y + dy_2 >= 0 && y + dy_2 < SIZE && board_copy[x + dx_2][y + dy_2] == player){
                    count2++;
                    dx_2 -= directions[i][0];
                    dy_2 -= directions[i][1];
                }
                if (count2 == 1){
                    if (isForbiddenMove(board_copy, newCoordinate, player) == NO){ // 判断第四颗棋子能否落下
                        int avail_five = 0; // 记录四子连珠两端能形成五连的数量
                        board_copy[newCoordinate.x][newCoordinate.y] = player; // 假设落下了第四颗棋子

                        // 看一看正方向第五个是不是空位
                        if (x + dx_1 >= 0 && x + dx_1 < SIZE && y + dy_1 >= 0 && y + dy_1 < SIZE && board_copy[x + dx_1][y + dy_1] == NOBODY){
                            struct placeStone newCoordinate = {x + dx_1, y + dy_1};
                            // 多看一格，确保不是长连
                            dx_1 += directions[i][0];
                            dy_1 += directions[i][1];
                            if (x + dx_1 < 0 || x + dx_1 >= SIZE || y + dy_1 < 0 || y + dy_1 >= SIZE || board_copy[x + dx_1][y + dy_1] != player){                      
                                if (isForbiddenMove(board_copy, newCoordinate, player) == NO){ // 判断第五颗棋子能否落下
                                    avail_five++;
                                }
                            }
                            // 撤销多看的一格
                            dx_1 -= directions[i][0];
                            dy_1 -= directions[i][1];
                        }
                        // 看一看反方向第五个是不是空位
                        if (x + dx_2 >= 0 && x + dx_2 < SIZE && y + dy_2 >= 0 && y + dy_2 < SIZE && board_copy[x + dx_2][y + dy_2] == NOBODY){
                            struct placeStone newCoordinate = {x + dx_2, y + dy_2};
                            // 多看一格，确保不是长连
                            dx_2 -= directions[i][0];
                            dy_2 -= directions[i][1];
                            if (x + dx_2 < 0 || x + dx_2 >= SIZE || y + dy_2 < 0 || y + dy_2 >= SIZE || board_copy[x + dx_2][y + dy_2] != player){  
                                if (isForbiddenMove(board_copy, newCoordinate, player) == NO){ // 判断第五颗棋子能否落下
                                    avail_five++;
                                }
                            }
                            // 撤销多看的一格
                            dx_2 += directions[i][0];
                            dy_2 += directions[i][1];
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
