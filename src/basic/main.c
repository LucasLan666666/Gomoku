// 如你所见，这是五子棋程序的主文件
// 本五子棋程序使用 utf-8 编码
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../gomoku.h"

int gameMode; // 游戏模式，1 表示双人对战，2 表示人机对战，3 表示退出游戏，-1表示输入有误
signed char computer; // 电脑执子，BLACK 为黑子，WHITE 为白子

int main() {
    #ifdef _WIN32
        system("chcp 65001"); // 设置 Windows 控制台编码为 utf-8
    #endif
    while (1) {
        homePage();
        switch (gameMode) {
            case 1:
                playerVsPlayer(); break;
            case 2:
                playerVsComputer(); break;
            case 3:
                end(); break;
        }
    }
}

// 初始化整个游戏，回到主页面，根据玩家输入确定游戏模式，读到 quit 或者 q 时退出游戏
void homePage(void) {
    int clear = system(CLEAR_SCREEN); // 清屏
    (void)clear;
    for (int i = 0; i < 15; i++) {
        printf("%s", HAPPY_GOMOKU[i]);
    }
    printf("作者：蓝宇舟\n");
    printf("欢迎来到五子棋游戏！一共有以下两种游戏模式：\n");
    printf("（1）：双人对战\n");
    printf("（2）：人机对战\n");
    printf("输入“quit”或者“q”可以退出游戏，此外，在游戏任何时候输入 EOF，也可以强制退出整个游戏\n");
    printf("（EOF 为文件结束符，Linux 下默认是“Ctrl + D”，Windows 下默认是“Ctrl + Z”后回车）\n");
    printf("请选择您的游戏模式（1：人人 2：人机）：");
    
    mygetline(line); // 从键盘读取输入到 line 中，根据结果对 gameMode 赋值
    while ((gameMode = inputCheckInHomePage()) == -1) {
            printf("您的输入有误，请重新输入：");
            mygetline(line);
    }

    printf("您选择了%s对战模式\n", (gameMode == 1) ? "人人" : "人机");
    if (gameMode == 2) {
        whoGoFirst(); // 决定人机模式的先手
    } else if (gameMode == 3) {
        end();
    }

    isRecord();
    if (gameRecord && readWritePermission) {
        createGameRecordFile();
    } else {
        printf("棋谱创建失败，没有足够权限，请尝试在其他目录下执行程序\n");
    }
}

// 直接清屏退出游戏
void end(void) {
    printf("\n感谢您的支持！有空常来玩儿~\n");
    sleep(2);
    int clear = system(CLEAR_SCREEN);
    (void)clear;
    exit(0);
}

// 提示玩家输入电脑执子的颜色，并修改 computer 的值
void whoGoFirst(void) {
    printf("下面请选择电脑所执子的颜色（1：黑色 2：白色）：");
    mygetline(line);            
    while (1) {
        if ((strcmp(line, "1") == 0) || (strcmp(line, "") == 0)) {
            computer = BLACK;
            break;
        } else if (strcmp(line, "2") == 0) { 
            computer = WHITE;
            break;
        } else {
            printf("您的输入有误，请重新输入：");
            mygetline(line);
        }
    }
    printf("您为电脑选择了%s\n", (computer == BLACK) ? "黑子" : "白子");
}