// 如你所见，这是五子棋程序的主文件
// 本五子棋程序使用utf-8编码，如果不能正常显示内容，请尝试在编译时加上参数 “-fexec-charset=utf-8”
#include <stdio.h>
#include <stdlib.h>
#include "gomoku.h"

int gameMode;  // 游戏模式，1表示双人对战，2表示人机对战

int main(){
    while (1){
        homePage();
        switch (gameMode){
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
void homePage(void){
    int result = system("clear");  // system函数会返回一个整数，如果不这样赋值，编译器会发出警告

    for (int i = 0; i < 15; i++){
        printf("%s", HAPPY_GOMOKU[i]);
    }
    printf("欢迎来到五子棋游戏！请选择你的游戏模式：\n");
    printf("（1）：人人对战\n");
    printf("（2）：人机对战\n");
    printf("输入“quit”或者“q”可以退出游戏(此外，在游戏任何时候输入EOF（文件结束符，linux 下默认是“Ctrl + D”），可以强制退出整个游戏)\n");
    
    mygetline();  // 从键盘读取输入到line中
    while (inputCheckInHomePage() == -1){  // 对玩家输入进行判断
        printf("你的输入有误，请重新输入：\n");
        mygetline();
    }
}