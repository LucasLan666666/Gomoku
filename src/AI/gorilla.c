#include <stdlib.h>
#include <time.h>
#include "../gomoku.h"

// 电脑随机落子，直接修改 innerBoard(注意要下在合法位置)
Coordinate gorilla(void){
    // 创建一颗虚拟棋子
    Coordinate coordinate;
    // 使用当前时间作为随机数种子
    srand(time(0));
    do{
        coordinate.x = getRandom(0, SIZE - 1);
        coordinate.y = getRandom(0, SIZE - 1);
    }while(!isValid(coordinate));
    return coordinate;
}

int getRandom(int min, int max){
    return min + rand() % (max - min + 1);
}
