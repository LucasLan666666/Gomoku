// 一代 AI，死于来不及复习，半成品
#include "../gomoku.h"

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