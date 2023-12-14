// 如你所见，这是五子棋程序的主文件
// 本五子棋程序使用utf-8编码，如果不能正常显示内容，请尝试在编译时加上参数 “-fexec-charset=utf-8”
#include <stdio.h>
#include <stdlib.h>
#include "gomoku.h"

int gameMode;  // 游戏模式，1表示双人对战，2表示人机对战，3表示读取棋谱，4表示退出游戏，-1表示输入有误

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
                readGameRecord();
                break;
            case 4:
                End();
                break;
        }
    }
}

// 初始化整个游戏，回到主页面，根据玩家输入确定游戏模式，读到quit或者q时退出游戏
void homePage(void){
    int clear = system("clear");  // 清屏

    for (int i = 0; i < 15; i++){
        printf("%s", HAPPY_GOMOKU[i]);
    }
    printf("欢迎来到五子棋游戏！请选择你的游戏模式：\n");
    printf("（1）：人人对战\n");
    printf("（2）：人机对战\n");
    printf("（3）：读取棋谱\n");
    printf("输入“quit”或者“q”可以退出游戏(此外，在游戏任何时候输入EOF（文件结束符，linux 下默认是“Ctrl + D”），可以强制退出整个游戏)\n");
    
    mygetline();  // 从键盘读取输入到line中，根据结果对gameMode赋值
    while ((gameMode = inputCheckInHomePage()) == -1){
            printf("你的输入有误，请重新输入：\n");
            mygetline();
    }
    if (gameMode == 3){
        printf("你选择了读取棋谱\n");
        printf("以下是棋谱文件，请输入你想要读入的棋谱：\n");
            mygetline();
            // 开发中...
        return;
    }
    if (gameMode == 4){
        End();
    }
    printf("你选择了%s对战模式\n", (gameMode == 1) ? "人人" : "人机");
    printf("是否记录棋谱？（y/n）\n");
    mygetline();            
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