// 大猩猩吼吼吼
#include <stdlib.h>
#include <time.h>
#include "../gomoku.h"

// 电脑随机落子，返回落子坐标
Coordinate gorilla(void) {
    // 创建一颗虚拟棋子
    Coordinate coordinate;
    // 使用当前时间作为随机数种子
    srand(time(0));
    // 将心中棋盘转换为虚拟棋盘
    signed char vBoard[SIZE][SIZE];
    initVBoard(vBoard);
    innerBoard2VBoard(vBoard);
    do{
        coordinate.x = getRandom(0, SIZE - 1);
        coordinate.y = getRandom(0, SIZE - 1);
    }while(!isValid(vBoard, coordinate, computer, NO));
    return coordinate;
}

signed char getRandom(signed char min, signed char max) {
    return min + rand() % (max - min + 1);
}
