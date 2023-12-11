// 关于棋盘的一些基础配置，包括棋盘的大小，棋盘的显示，棋盘的初始化等等
#include <stdio.h>
#include <stdlib.h>
#include "macro.h"

extern int mode; // 游戏模式，1表示双人对战，2表示人机对战

// 空棋盘模板 
char arrayForEmptyBoard[SIZE][SIZE*CHARSIZE+1] = 
{
		"┏┯┯┯┯┯┯┯┯┯┯┯┯┯┓",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┠┼┼┼┼┼┼┼┼┼┼┼┼┼┨",
		"┗┷┷┷┷┷┷┷┷┷┷┷┷┷┛"
};

// 以下是棋子的图案
char play1Pic[]="●";  // 黑棋子
char play1CurrentPic[]="▲"; // 黑棋子的当前落子位置
char play2Pic[]="◎";  // 白棋子
char play2CurrentPic[]="△"; // 白棋子的当前落子位置

// 当前的棋盘的格局 
int arrayForInnerBoardLayout[SIZE][SIZE];

// 显示的棋盘 
char arrayForDisplayBoard[SIZE][SIZE*CHARSIZE+1];


int lastPlayerMoveStone[2];  // 上一步玩家落子的坐标
int currentPlayerMoveStone[2];  // 当前玩家落子的坐标
int player;  // 当前等待落子的玩家，1表示黑方，2表示白方

// 初始化一个空棋盘格局 
void initRecordBoard(void){
	//通过双重循环，将arrayForInnerBoardLayout清0
    int i,j;
    for (i=0;i<SIZE;i++)
        for (j=0;j<SIZE;j++)
            arrayForInnerBoardLayout[i][j]=0;
}

//将arrayForInnerBoardLayout中记录的棋子位置，转化到arrayForDisplayBoard中
void innerLayoutToDisplayArray(void){
	//第一步：将arrayForEmptyBoard中记录的空棋盘，复制到arrayForDisplayBoard中
    int i, j;
    for (i=0;i<SIZE;i++)
        for (j=0;j<SIZE*CHARSIZE+1;j++)
            arrayForDisplayBoard[i][j]=arrayForEmptyBoard[i][j];
    //第二步：扫描arrayForInnerBoardLayout，当遇到非0的元素，将●或者◎复制到arrayForDisplayBoard的相应位置上
	//注意：arrayForDisplayBoard所记录的字符是中文字符，每个字符占2个字节。●和◎也是中文字符，每个也占2个字节。
    for (i=0;i<SIZE;i++){
        for (j=0;j<SIZE;j++){
            switch (arrayForInnerBoardLayout[i][j]){
                case (1):
                    arrayForDisplayBoard[i][j * CHARSIZE] = play1Pic[0];
                    arrayForDisplayBoard[i][j * CHARSIZE + 1] = play1Pic[1];
                    arrayForDisplayBoard[i][j * CHARSIZE + 2] = play1Pic[2];
                    break;
                case (2):
                    arrayForDisplayBoard[i][j * CHARSIZE] = play2Pic[0];
                    arrayForDisplayBoard[i][j * CHARSIZE + 1] = play2Pic[1];
                    arrayForDisplayBoard[i][j * CHARSIZE + 2] = play2Pic[2];
                    break;
                case (-1):
                    arrayForDisplayBoard[i][j * CHARSIZE] = play1CurrentPic[0];
                    arrayForDisplayBoard[i][j * CHARSIZE + 1] = play1CurrentPic[1];
                    arrayForDisplayBoard[i][j * CHARSIZE + 2] = play1CurrentPic[2];
                    break;
                case (-2):
                    arrayForDisplayBoard[i][j * CHARSIZE] = play2CurrentPic[0];
                    arrayForDisplayBoard[i][j * CHARSIZE + 1] = play2CurrentPic[1];
                    arrayForDisplayBoard[i][j * CHARSIZE + 2] = play2CurrentPic[2];
                    break;
            }
            
        }
    }
}

//显示棋盘格局 
void displayBoard(void){
	int i;
	// 清屏
    int result = system("clear");  // system函数会返回一个整数，如果不这样赋值，编译器会发出警告

    // 输出提示信息
    if (mode == 1)
        printf("双 人 模 式\n\n");
    else
        printf("人 机 模 式\n\n");
    printf("本游戏支持一些指令：\n");
    printf("“quit”-回到主页面  “regret”-悔棋\n\n");
    
    // 将arrayForDisplayBoard输出到屏幕上
    for (i = 0; i < SIZE; i++){
        printf("%3d %s\n", SIZE - i, arrayForDisplayBoard[i]);
    }

    // 输出最下面的一行字母A B ....
    printf("    ");
    for (i = 0; i < SIZE; i++)
        printf("%2c", 'A' + i);
    printf("\n\n");

    // 输出当前等待落子的玩家
    if (player == 1)
        printf("现在请黑方落子：");
    else
        printf("现在请白方落子：");
}