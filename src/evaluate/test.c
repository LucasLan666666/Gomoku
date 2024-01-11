#include "../gomoku.h"
#include <stdio.h>

// 眠三函数功能测试（眠三判定太复杂了，所以专门开个函数测试一下）
void testForSleepThree(Coordinate coordinate) {
    // 将心中棋盘转换为虚拟棋盘
    signed char vBoard[SIZE][SIZE];
    initVBoard(vBoard);
    innerBoard2VBoard(vBoard);

    printf("    眠三能形成的冲四数量：%d\n", sleepThree(vBoard, coordinate, player));
}