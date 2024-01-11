// 本文件记录了决策树的相关操作
#include <stdlib.h>
#include "../gomoku.h"

// 创建一个新的结点
Node* createNode(signed char board[SIZE][SIZE], signed char player, signed char floor) {
    Node* pnode = (Node*)malloc(sizeof(Node));
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            pnode->board[i][j] = board[i][j];
        }
    }
    pnode->player = player;
    pnode->score = 0;
    pnode->floor = floor;
    pnode->numChildren = 0;
    return pnode;
}

// 释放结点及其子节点的内存空间
void freeNode(Node* pnode) {
    if (pnode == NULL) {
        return;
    }
    for (int i = 0; i < pnode->numChildren; i++) {
        freeNode(pnode->children[i]);
    }
    free(pnode);
}

// 构建决策树，并使用 alpha-beta 剪枝优化
void buildDecisionTree(Node* pnode, signed char depth, int alpha, int beta) {
    // 递归终止条件：达到最大深度
    if (depth == 0) {
        pnode->score = evaluate(pnode->board, pnode->player);
        return;
    }

    // 生成所有可能的下一步棋局
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (pnode->board[i][j] == 0) {
                // 尝试在空位落子
                signed char newBoard[SIZE][SIZE];
                for (int k = 0; k < SIZE; k++) {
                    for (int l = 0; l < SIZE; l++) {
                        newBoard[k][l] = pnode->board[k][l];
                    }
                }
                newBoard[i][j] = pnode->player;

                // 创建新节点
                Node* childNode = createNode(newBoard, -pnode->player, pnode->floor + 1);
                pnode->children[pnode->numChildren++] = childNode;

                // 使用 Alpha-Beta 剪枝优化
                if (pnode->type == MAX) {
                    alpha = alpha > pnode->score ? alpha : pnode->score;
                    if (beta <= alpha) {
                        return;
                    }
                } else {
                    beta = beta < pnode->score ? beta : pnode->score;
                    if (beta <= alpha) {
                        return;
                    }
                }
                buildDecisionTree(childNode, depth - 1, alpha, beta);
            }
        }
    }
}

// 从叶子节点开始回溯，找到最优解的坐标
// Coordinate findBestMove(Node* pnode, int* row, int* col) {
//     if (pnode->floor == 0) {
//         // 已经回溯到根节点，返回最优解的坐标
//         *row = node->bestRow;
//         *col = node->bestCol;
//         return;
//     }

//     // 找到最优子节点
//     Node* bestChild = NULL;
//     for (int i = 0; i < node->numChildren; i++) {
//         Node* child = node->children[i];
//         if (bestChild == NULL || (node->type == MAX && child->score > bestChild->score) ||
//             (node->type == MIN && child->score < bestChild->score)) {
//             bestChild = child;
//         }
//     }

//     // 回溯到父节点，记录最优解的坐标
//     node->bestRow = bestChild->lastRow;
//     node->bestCol = bestChild->lastCol;

//     findBestMove(bestChild->parent, row, col);
// }