#include "../gomoku.h"

// AI 下棋，接受电脑颜色作为参数，调整下棋策略，返回落子坐标
Coordinate AI(signed char computer) {
    // 创建一颗虚拟棋子
    Coordinate coordinate;
    if (computer == BLACK) {
        coordinate = AI_black(); // 黑棋策略
    } else {
        coordinate = AI_white(); // 白棋策略
    }
    return coordinate;
}

// AI 执黑
Coordinate AI_black() {
    // 创建一颗虚拟棋子
    Coordinate coordinate;

    // 先布局
    if (stepNum == 0) {
        // 天元开局
        coordinate.x = SIZE / 2;
        coordinate.y = SIZE / 2;
    } else if (stepNum == 2) {
        // 白棋位置，看看能不能浦月开局
        if (innerBoard[SIZE / 2 + 1][SIZE / 2 + 1].player == WHITE) {
            coordinate.x = SIZE / 2 + 1;
            coordinate.y = SIZE / 2 - 1;
        } else if (innerBoard[SIZE / 2 + 1][SIZE / 2 - 1].player == WHITE) {
            coordinate.x = SIZE / 2 - 1;
            coordinate.y = SIZE / 2 - 1;
        } else if (innerBoard[SIZE / 2 - 1][SIZE / 2 - 1].player == WHITE) {
            coordinate.x = SIZE / 2 - 1;
            coordinate.y = SIZE / 2 + 1;
        } else if (innerBoard[SIZE / 2 - 1][SIZE / 2 + 1].player == WHITE) {
            coordinate.x = SIZE / 2 + 1;
            coordinate.y = SIZE / 2 + 1;
        // 看看能不能花月开局
        } else if (innerBoard[SIZE / 2][SIZE / 2 + 1].player == WHITE) {
            coordinate.x = SIZE / 2 + 1;
            coordinate.y = SIZE / 2 + 1;
        } else if (innerBoard[SIZE / 2 + 1][SIZE / 2].player == WHITE) {
            coordinate.x = SIZE / 2 + 1;
            coordinate.y = SIZE / 2 - 1;
        } else if (innerBoard[SIZE / 2][SIZE / 2 - 1].player == WHITE) {
            coordinate.x = SIZE / 2 - 1;
            coordinate.y = SIZE / 2 - 1;
        } else if (innerBoard[SIZE / 2 - 1][SIZE / 2].player == WHITE) {
            coordinate.x = SIZE / 2 - 1;
            coordinate.y = SIZE / 2 + 1;
        // 对方走棋不满足花浦月开局条件，开始使用决策树算法
        coordinate = gorilla();
        }
    } else {
        // 开局布阵完毕，用真正的AI判断
        coordinate = trueAI();
    }
    return coordinate;
}

// AI 执白
Coordinate AI_white() {
    // 创建一颗虚拟棋子
    Coordinate coordinate;

    // 先防守
    if (stepNum == 1) {
        signed char dx = 0;
        signed char dy = 0;
        Coordinate first_black = stepRecord[0];
        if (first_black.x >= SIZE / 2) {
            dx = first_black.x - SIZE / 2;
            coordinate.x = first_black.x - 1;
        } else if (first_black.x < SIZE / 2) {
            dx = SIZE / 2 - first_black.x;
            coordinate.x = first_black.x + 1;
        }
        if (first_black.y >= SIZE / 2) {
            dy = first_black.y - SIZE / 2;
            coordinate.y = first_black.y - 1;
        } else if (first_black.y < SIZE / 2) {
            dy = SIZE / 2 - first_black.y;
            coordinate.y = first_black.y + 1;
        }
        if (dx > dy) {
            coordinate.y = first_black.y;
        } else {
            coordinate.x = first_black.x;
        }
    } else {
        // 开局布阵完毕，用真正的AI判断
        coordinate = trueAI();
    }
    return coordinate;
}

// 真正的AI
Coordinate trueAI(void) {
    // 声明一颗虚拟棋子
    Coordinate coordinate;

    // 将心中棋盘转换为虚拟棋盘
    signed char vBoard[SIZE][SIZE];
    initVBoard(vBoard);
    innerBoard2VBoard(vBoard);

    // 创建根节点
    Node* root = createNode(vBoard, player, 0); // 创建根节点

    // 构建决策树
    buildDecisionTree(root, DEPTH, -INFTY, INFTY);
    
    // 释放内存
    freeNode(root);
    return coordinate;
}
