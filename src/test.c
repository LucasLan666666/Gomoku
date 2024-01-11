#include "gomoku.h"
#include <stdio.h>

// 眠三函数功能测试
void testForSleepThree(struct placeStone coordinate){
    // 将心中棋盘转换为虚拟棋盘
    int vBoard[SIZE][SIZE];
    initVBoard(vBoard);
    innerBoard2VBoard(vBoard);

    printf("    眠三能形成的冲四数量：%d\n", sleepThree(vBoard, coordinate, player));
}