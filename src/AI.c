#include "gomoku.h"

// AI 下棋，接受电脑颜色作为参数，调整下棋策略，返回落子坐标
struct placeStone AI(int computer){
    // 创建一颗虚拟棋子
    struct placeStone coordinate;
    if (computer == BLACK){
        coordinate = AI_black(); // 黑棋策略
    }else{
        coordinate = AI_white(); // 白棋策略
    }
    return coordinate;
}

// AI 执黑
struct placeStone AI_black(){
    // 创建一颗虚拟棋子
    struct placeStone coordinate;

    // 先布局
    if (stepNum == 0){
        // 天元开局
        coordinate.x = 7;
        coordinate.y = 7;
    }else if (stepNum == 2){
        // 白棋位置，看看能不能浦月开局
        if (innerBoard[8][8].player == WHITE){
            coordinate.x = 8;
            coordinate.y = 6;
        }else if (innerBoard[8][6].player == WHITE){
            coordinate.x = 6;
            coordinate.y = 6;
        }else if (innerBoard[6][6].player == WHITE){
            coordinate.x = 6;
            coordinate.y = 8;
        }else if (innerBoard[6][8].player == WHITE){
            coordinate.x = 8;
            coordinate.y = 8;
        // 看看能不能花月开局
        }else if (innerBoard[7][8].player == WHITE){
            coordinate.x = 8;
            coordinate.y = 8;
        }else if (innerBoard[8][7].player == WHITE){
            coordinate.x = 8;
            coordinate.y = 6;
        }else if (innerBoard[7][6].player == WHITE){
            coordinate.x = 6;
            coordinate.y = 6;
        }else if (innerBoard[6][7].player == WHITE){
            coordinate.x = 6;
            coordinate.y = 8;
        // 对方走棋不满足花浦月开局条件，开始使用决策树算法
        coordinate = gorilla();
        }
    }else{
        // 开局布阵完毕，用决策树判断
        coordinate = gorilla();
    }
    return coordinate;
}

// AI 执白
struct placeStone AI_white(){
    // 创建一颗虚拟棋子
    struct placeStone coordinate;

    // 先防守
    if (stepNum == 1){
        int dx = 0;
        int dy = 0;
        struct placeStone first_black = stepRecord[0];
        if (first_black.x >= 7){
            dx = first_black.x - 7;
            coordinate.x = first_black.x - 1;
        }else if (first_black.x < 7){
            dx = 7 - first_black.x;
            coordinate.x = first_black.x + 1;
        }
        if (first_black.y >= 7){
            dy = first_black.y - 7;
            coordinate.y = first_black.y - 1;
        }else if (first_black.y < 7){
            dy = 7 - first_black.y;
            coordinate.y = first_black.y + 1;
        }
        if (dx > dy){
            coordinate.y = first_black.y;
        }else{
            coordinate.x = first_black.x;
        }
    }else{
        // 开局布阵完毕，用决策树判断
        coordinate = gorilla();
    }
    return coordinate;
}
