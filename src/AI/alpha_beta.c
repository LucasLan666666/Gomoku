// 本文件是 alpha-beta 剪枝算法的实现(搞不出来，暂时放弃)
#include "../gomoku.h"

// 通过 alpha-beta 剪枝便遍历决策树，找到最优解
Coordinate alphaBetaPruning(Node *pnode, signed char depth, int alpha, int beta) {
    // 递归终止条件：达到最大深度或者棋局已经结束
    if (getWinner(pnode->board) != NOBODY) { // 因为 getWinner 是对当前棋局判断是否出现胜者，所以如果已经出现，那么胜者只可能来自上一层
        pnode->score = (pnode->type == MIN) ? INFTY : -INFTY;
        return pnode->coordinate;
    } else if (depth == 0) {
        pnode->score = evaluate(pnode->board, computer);
        return pnode->coordinate;
    }

    // 初始化最优解和最优分数
    Coordinate bestCoordinate = {-1, -1};
    int bestScore = (pnode->type == MAX) ? -INFTY : INFTY;

    // 遍历子节点
    Node *pchild = pnode->pChildren;
    for (int i = 0; i < pnode->numChildren; i++) {
       // 以当前子节点为根节点，向下搜索到深度为 1 的子节点，计算其分数 score，并更新当前节点的分数。
        int score = buildOneStepDecisionTree(pchild + i, depth - 1, alpha, beta);

        // 更新最优解和最优分数
        if ((pnode->type == MAX && score > bestScore) || (pnode->type == MIN && score < bestScore)) {
            bestCoordinate = (pchild + i)->coordinate;
            bestScore = score;
        }

        // alpha-beta 剪枝
        if (pnode->type == MAX) {
            if (score >= beta) {
                pnode->score = score;
                return bestCoordinate;
            }
            if (score > alpha) {
                alpha = score;
            }
        } else {
            if (score <= alpha) {
                pnode->score = score;
                return bestCoordinate;
            }
            if (score < beta) {
                beta = score;
            }
        }
    }

    // 更新当前节点的最优分数
    pnode->score = bestScore;

    // 返回最优解
    return bestCoordinate;
}

// 构建决策树，搜索到深度为 1 的子节点，并返回其分数 score
int buildOneStepDecisionTree(Node *pnode, signed char depth, int alpha, int beta) {
    // 递归终止条件：达到最大深度或者棋局已经结束
    if (getWinner(pnode->board) != NOBODY) { // 因为 getWinner 是对当前棋局判断是否出现胜者，所以如果已经出现，那么胜者只可能来自上一层
        pnode->score = (pnode->type == MIN) ? INFTY : -INFTY;
        return pnode->score;
    } else if (depth == 0) {
        pnode->score = evaluate(pnode->board, computer);
        return pnode->score;
    }

    // 遍历子节点
    Node *pchild = pnode->pChildren;
    for (int i = 0; i < pnode->numChildren; i++) {
        // 以当前子节点为根节点，向下搜索到深度为 1 的子节点，计算其分数 score，并更新当前节点的分数。
        int score = buildOneStepDecisionTree(pchild + i, depth - 1, alpha, beta);

        // 更新当前节点的最优分数
        if ((pnode->type == MAX && score > pnode->score) || (pnode->type == MIN && score < pnode->score)) {
            pnode->score = score;
        }

        // alpha-beta 剪枝
        if (pnode->type == MAX) {
            if (score >= beta) {
                return score;
            }
            if (score > alpha) {
                alpha = score;
            }
        } else {
            if (score <= alpha) {
                return score;
            }
            if (score < beta) {
                beta = score;
            }
        }
    }

    // 返回当前节点的最优分数
    return pnode->score;
}
