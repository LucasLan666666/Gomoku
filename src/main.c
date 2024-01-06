// 如你所见，这是五子棋程序的主文件
// 本五子棋程序使用 utf-8 编码，如果不能正常显示内容，请尝试在编译时加上参数 “-fexec-charset=utf-8”
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gomoku.h"

int gameMode;  // 游戏模式，1 表示双人对战，2 表示人机对战，3 表示退出游戏，-1表示输入有误
int computer;  // 电脑执子，BLACK 为黑子，WHITE 为白子

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
            case 3:
                End();
                break;
        }
    }
}

// 初始化整个游戏，回到主页面，根据玩家输入确定游戏模式，读到 quit 或者 q 时退出游戏
void homePage(void){
    int clear = system("clear");  // 清屏

    for (int i = 0; i < 15; i++){
        printf("%s", HAPPY_GOMOKU[i]);
    }
    printf("作者：蓝宇舟\n");
    printf("欢迎来到五子棋游戏！请选择你的游戏模式：\n");
    printf("（1）：人人对战\n");
    printf("（2）：人机对战\n");
    printf("输入“quit”或者“q”可以退出游戏(此外，在游戏任何时候输入EOF（文件结束符，linux 下默认是“Ctrl + D”），可以强制退出整个游戏)\n");
    
    mygetline();  // 从键盘读取输入到 line 中，根据结果对 gameMode 赋值
    while ((gameMode = inputCheckInHomePage()) == -1){
            printf("你的输入有误，请重新输入：\n");
            mygetline();
    }

    printf("你选择了%s对战模式\n", (gameMode == 1) ? "人人" : "人机");
    if (gameMode == 2){
        whoGoFirst();  // 决定人机模式的先手
    }else if (gameMode == 3){
        End();
    }

    isRecord();
    if (gameRecord && readWritePermission){
        createGameRecordFile();
    }else{
        printf("棋谱创建失败，没有足够权限，请尝试在其他目录下执行程序\n");
    }
}

// 直接清屏退出游戏
void End(void){
    int clear = system("clear");
    exit(0);
}

// 转换玩家，黑方下完白方下，白方下完黑方下
void changePlayer(void){
    player = (player == BLACK) ? WHITE : BLACK;
}

// 提示玩家输入自己执子的颜色，并修改 computer 的值
void whoGoFirst(void){
    printf("下面请选择您所执子的颜色（黑色为 1，白色为 2）：\n");
    mygetline();            
    while (1){
        if ((strcmp(line, "1") == 0) || (strcmp(line, "") == 0)){
            computer = WHITE;
            break;
        }else if (strcmp(line, "2") == 0){ 
            computer = BLACK;
            break;
        }else{
            printf("你的输入有误，请重新输入：\n");
            mygetline();
        }
    }
    printf("你选择了%s\n", (computer == BLACK) ? "白子" : "黑子");
}