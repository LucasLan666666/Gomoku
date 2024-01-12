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
        } else {
            // 对方走棋不满足花浦月开局条件，开始使用 AI 算法
            coordinate = AI_Second();
        }
    } else {
        // 开局布阵完毕，用 AI2.0 判断
        coordinate = AI_Second();
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
        // 开局布阵完毕，用 AI2.0 判断
        coordinate = AI_Second();
    }
    return coordinate;
}

// AI1.0
Coordinate AI_First(void) {
    // 声明一颗虚拟棋子
    Coordinate coordinate;

    // 将心中棋盘转换为虚拟棋盘
    signed char vBoard[SIZE][SIZE];
    initVBoard(vBoard);
    innerBoard2VBoard(vBoard);

    // 创建根节点
    Node *root = createRoot(vBoard, computer); // 创建根节点

    // 构建决策树
    buildDecisionTree(root, DEPTH);

    // 通过 alpha-beta 剪枝便遍历决策树，找到最优解
    coordinate = alphaBetaPruning(root, DEPTH, -INFTY, INFTY);
    
    // 释放内存
    freeNode(root);
    return coordinate;
}

// AI2.0
Coordinate AI_Second(void){

    // 将心中棋盘转换为虚拟棋盘
    signed char board[SIZE][SIZE];
    initVBoard(board);
    innerBoard2VBoard(board);

    // 创建预测落子列表
    Pre sequence[MAXSTEP*MAXSTEP];

    // 列表的真实长度
    int len = 0;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            Coordinate temp1 = {i, j};
            if (
                    board[i][j] == NOBODY
                &&  isValid(board, temp1, computer, NO)
            ){
                // 为了防止修改原棋盘，这里需要复制一份
                signed char board_copy[SIZE][SIZE];
                initVBoard(board_copy);
                copyBoard(board_copy, board);
                // 落下第一颗棋子
                board_copy[i][j] = computer;
                // 看下这一步能否形成五连，可以直接返回
                if (judgeWin(board_copy) == computer) {
                    return temp1;
                }
                // 如果游戏没有结束，下面通过循环，看看能不能落下第二颗棋子
                for (int k = 0; k < SIZE; k++){
                    for (int l = 0; l < SIZE; l++){
                        Coordinate temp2 = {k, l};
                        if (
                                board_copy[k][l] == NOBODY
                            &&  isValid(board, temp2, -computer, NO)
                        ){
                            sequence[len].first = temp1;
                            sequence[len].second = temp2;
                            len++;
                        }
                    }
                }
            }
        }
    }

    // 遍历预测落子列表，对每一种情况进行打分
    for (int i = 0; i < len; i++) {
        // 为了防止修改原棋盘，这里需要复制一份
        signed char board_copy[SIZE][SIZE];
        initVBoard(board_copy);
        copyBoard(board_copy, board);
        // 落下第一颗棋子
        board_copy[sequence[i].first.x][sequence[i].first.y] = computer;
        // 落下第二颗棋子
        board_copy[sequence[i].second.x][sequence[i].second.y] = -computer;
        // 打分
        sequence[i].score = evaluate(board_copy, computer);
    }

    int minScore = sequence[0].score; // 记录当前层的最低分
    int maxMinScore = sequence[0].score; // 记录所有层的最低分中的最高分
    Coordinate bestStep = sequence[0].first; // 记录最佳落子

    // 从预测落子列表中找到最高分的落子，选择对应的第一颗棋子
    for (int i = 1; i < len; i++) {
        if (   sequence[i].first.x == sequence[i-1].first.x
            && sequence[i].first.y == sequence[i-1].first.y
            ) { // 在第一颗棋子相同的情况下，不断更新最低分
            if (sequence[i].score <= minScore) {
                minScore = sequence[i].score;
            }
        } else {  // 当第一颗棋子发生改变时
            if (maxMinScore <= minScore) {
                maxMinScore = minScore; // 上一层已经遍历完，更新最低分中的最高分
                bestStep = sequence[i - 1].first; // 更新最佳落子
            }
            minScore = sequence[i].score; // 重置最低分
        }
    }
    if (maxMinScore <= minScore) {
        bestStep = sequence[len - 1].first; // 更新最佳落子
    }
    return bestStep;
}