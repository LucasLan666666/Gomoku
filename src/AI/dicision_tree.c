// 本文件记录了决策树的相关操作（暂时搁置，debug de 不出来，麻了）
#include <stdlib.h>
#include "../gomoku.h"

// 创建一个根结点，返回指向该结点的指针
Node *createRoot(signed char board[SIZE][SIZE], signed char player) {
    Node *root = (Node*)malloc(sizeof(Node));
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            root->board[i][j] = board[i][j];
        }
    }
    root->pParent = NULL;
    root->player = player;
    root->score = 0;
    root->type = MAX;
    root->pChildren = NULL;
    root->numChildren = 0;
    return root;
}

// 为父节点添加子节点，返回指向子节点数组的指针
Node *addChildrenNode(Node *pParent, unsigned char numChildren) {
    pParent->numChildren = numChildren;
    if (numChildren == 0) {
        return NULL;
    } else {
        return (Node*)malloc(sizeof(Node) * numChildren);
    }
}

// 释放结点及其子节点的内存空间
void freeNode(Node *pnode) {
    if (pnode == NULL) {
        return;
    }
    for (int i = 0; i < pnode->numChildren; i++) {
        freeNode(pnode->pChildren + i);
    }
    free(pnode);
}

// 构建决策树
void buildDecisionTree(Node *pnode, signed char depth) {
    // 递归终止条件：达到最大深度或者棋局已经结束
    if (getWinner(pnode->board) != NOBODY) { // 因为 getWinner 是对当前棋局判断是否出现胜者，所以如果已经出现，那么胜者只可能来自上一层
        pnode->score = (pnode->type == MIN) ? INFTY : -INFTY;
        return;
    } else if (depth == 0) {
        pnode->score = evaluate(pnode->board, computer);
        return;
    }

    // 数一数能建立多少个子节点
    unsigned char numChildren = 0;

    // 遍历棋盘上的每一个有效空位
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            // 将要落子的坐标
            Coordinate coordinate = {i, j};
            // 判断是否可以落子，可以落子就增加子节点数量
            if (pnode->board[i][j] == NOBODY && isForbiddenMove(pnode->board, coordinate, pnode->player) == NO) {
                numChildren++;
            }
        }
    }

    // 创建子节点列表
    Node *pchild = addChildrenNode(pnode, numChildren);

    // 为父节点添加子节点
    int k = 0;
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            // 生成可能的下一步棋局
            signed char newBoard[SIZE][SIZE];
            copyBoard(newBoard, pnode->board);
           // 将要落子的坐标
            Coordinate coordinate = {i, j};
            // 判断是否可以落子，可以落子就创建一个子节点
            if (newBoard[i][j] == NOBODY && isForbiddenMove(newBoard, coordinate, pnode->player) == NO) {
                // 在空位落子
                newBoard[i][j] = pnode->player;

                // 更新子节点信息
                for (int m = 0; m < SIZE; m++) {
                    for (int n = 0; n < SIZE; n++) {
                        pchild[k].board[m][n] = newBoard[m][n];
                    }
                }
                pchild[k].coordinate = coordinate;
                pchild[k].pParent = pnode;
                pchild[k].player = -pnode->player;
                pchild[k].type = -pnode->type;
                // 递归构建子树
                buildDecisionTree(pchild + k, depth - 1);
            }
        }
    }
}

// 从叶子节点开始回溯，找到最优解的坐标
// Coordinate findBestMove(Node *pnode, int *row, int *col) {
//     if (pnode->floor == 0) {
//        // 已经回溯到根节点，返回最优解的坐标
//         *row = node->bestRow;
//         *col = node->bestCol;
//         return;
//     }

//    // 找到最优子节点
//     Node *bestChild = NULL;
//     for (int i = 0; i < node->numChildren; i++) {
//         Node *child = node->children[i];
//         if (bestChild == NULL || (node->type == MAX && child->score > bestChild->score) ||
//             (node->type == MIN && child->score < bestChild->score)) {
//             bestChild = child;
//         }
//     }

//    // 回溯到父节点，记录最优解的坐标
//     node->bestRow = bestChild->lastRow;
//     node->bestCol = bestChild->lastCol;

//     findBestMove(bestChild->parent, row, col);
// }