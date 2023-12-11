// 如你所见，这是五子棋程序的主文件
// 本五子棋程序使用utf-8编码，如果不能正常显示内容，请尝试在编译时加上参数 “-fexec-charset=utf-8”
#include <stdio.h>
#include <stdlib.h>
#include "gobang.h"
int mode;  // 游戏模式，1表示双人对战，2表示人机对战

int main(){
    while(1){
        initGame();
        switch (mode){
            case 1:
                playerVsPlayer();
                break;
            case 2:
                playerVsComputer();
                break;
            default:
                break;
        }
    }
}

// 初始化整个游戏，回到主页面，根据玩家输入确定游戏模式
void initGame(void){
    int result = system("clear");  // system函数会返回一个整数，如果不这样赋值，编译器会发出警告
    printf("欢迎来到五子棋游戏！请选择你的游戏模式：\n");
    printf("（1）：人人对战\n");
    printf("（2）：人机对战\n");
    printf("游戏中任意时刻输入文件结束符EOF可以退出游戏（linux系统下默认是“ctrl+D”）\n");
    if (scanf("%d", &mode) == -1) // 读到EOF，退出游戏
        exit(0);
    while (getchar() != '\n');  // 清空输入缓冲区
    switch (mode){
        case 1:
            printf("你选择了人人对战模式（按下Enter继续）");
            getchar();
            break;
        case 2:
            printf("你选择了人机对战模式（按下Enter继续）");
            getchar();
            break;
        default:
            printf("你的输入有误，请重新输入！（按下Enter继续）");
            getchar();
            initGame();
    }
}