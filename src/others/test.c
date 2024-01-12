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

// 测试电脑运算速度
Coordinate testSpeed(void){
    Coordinate coordinate;
    for (int i = 0; i < MAXSTEP; i++) {
        for (int j = 0; j < MAXSTEP; j++) {
            coordinate = gorilla();
        }
    }
    // 结论：不利用剪枝操作时，最多搜两层，否则会超时
    return coordinate;
}