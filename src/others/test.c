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

// 测试电脑下棋能力，先设定几个预定的走法
Coordinate testAI(void) {
    Coordinate coordinate;
    if (stepNum == 0) {
        coordinate.x = 0;
        coordinate.y = 5;
    } else if (stepNum == 2) {
        coordinate.x = 1;
        coordinate.y = 5;
   // } else if (stepNum == 4) {
   //     coordinate.x = 14;
   //     coordinate.y = 0;
   // } else if (stepNum == 6) {
   //     coordinate.x = 14;
   //     coordinate.y = 14;
   // } else if (stepNum == 8) {
   //     coordinate.x = 2;
   //     coordinate.y = 3;
    } else {
       // 开局布阵完毕，用 AI2.0 判断
        coordinate = AI_Second();
       // coordinate = gorilla();
    }
    return coordinate;
}