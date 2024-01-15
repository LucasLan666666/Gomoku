// 二代 AI，用最原始的数组方法，进行一层暴力运算，实现思路也为 min-max，但是没有剪枝
#include "../gomoku.h"

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
                if (getWinner(board_copy) == computer) {
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
    int maxMinScore = -INFTY; // 记录所有层的最低分中的最高分
    Coordinate bestStep = sequence[0].first; // 记录最佳落子

   // 从预测落子列表中找到最高分的落子，选择对应的第一颗棋子
    for (int i = 1; i < len; i++) {
        if (   sequence[i].first.x == sequence[i-1].first.x
            && sequence[i].first.y == sequence[i-1].first.y
            ) { // 在第一颗棋子相同的情况下，不断更新最低分
            if (sequence[i].score <= minScore) {
                minScore = sequence[i].score;
            }
        } else { // 当第一颗棋子发生改变时
            if (maxMinScore <= minScore) {
                maxMinScore = minScore; // 上一层已经遍历完，更新最低分中的最高分
                bestStep = sequence[i - 1].first; // 更新最佳落子
            }
            minScore = sequence[i].score; // 重置最低分
        }
    }
    if (maxMinScore <= minScore) {
        maxMinScore = minScore; // 更新最低分中的最高分
        bestStep = sequence[len - 1].first; // 更新最佳落子
    }

   // 如果已知必死无疑，挣扎一下
    if (maxMinScore == -2000000000) {
        bestStep = struggle(board, computer);
    }
    return bestStep;
}