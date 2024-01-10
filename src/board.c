// 关于棋盘的一些基础配置，包括棋盘的大小，棋盘的显示，棋盘的初始化等等
#include <stdio.h>
#include <stdlib.h>
#include "gomoku.h"

// 空棋盘模板 
char emptyDisplayBoard[SIZE][(2 * SIZE - 1) * CHARSIZE + 1] = {
	"┌─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┐",
	"├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤",
	"├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤",
	"├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤",
	"├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤",
	"├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤",
	"├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤",
	"├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤",
	"├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤",
	"├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤",
	"├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤",
	"├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤",
	"├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤",
	"├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤",
	"└─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┘"
};

// 以下是棋子的图案
char play1Pic[]="●";  // 黑棋子
char play1CurrentPic[]="▲"; // 黑棋子的当前落子位置
char play2Pic[]="◎";  // 白棋子
char play2CurrentPic[]="△"; // 白棋子的当前落子位置

// 心中的的棋盘的格局 
struct stone innerBoard[SIZE][SIZE];

// 显示的棋盘 
char displayBoard[SIZE][(2 * SIZE - 1) * CHARSIZE + 1];

// 当前等待落子的玩家，1表示黑方，2表示白方
int player;

// 初始化一个空棋盘格局 
void initInnerBoard(void){
	//通过三重循环，将 innerBoard 清 0
    int i, j, k;
    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++){
            innerBoard[i][j].current = NO;
            innerBoard[i][j].player = NOBODY;
        }
}

// 将虚拟棋盘清零
void initVBoard(int vBoard[SIZE][SIZE]){
    int i, j;
    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++){
            vBoard[i][j] = NOBODY;
        }
}

//将 innerBoard 中记录的棋子位置，转化到 displayBoard 中
void innerBoard2Displayboard(void){
	//第一步：将 emptyDisplayBoard 中记录的空棋盘，复制到 displayBoard 中
    int i, j;
    for (i = 0; i < SIZE; i++)
        for (j = 0; j < (2 * SIZE - 1) * CHARSIZE + 1; j++)
            displayBoard[i][j] = emptyDisplayBoard[i][j];
    //第二步：扫描 innerBoard，当遇到非 0 的元素，将 ● 或者 ◎ 复制到 displayBoard 的相应位置上
	//注意：displayBoard 所记录的字符是中文字符，每个字符占 2 个字节。● 和 ◎ 也是中文字符，每个也占 2 个字节。
    for (i = 0; i < SIZE; i++){
        for (j = 0; j < SIZE; j++){
            if (innerBoard[i][j].current == NO){
                if (innerBoard[i][j].player == BLACK){
                    displayBoard[i][2 * j * CHARSIZE] = play1Pic[0];
                    displayBoard[i][2 * j * CHARSIZE + 1] = play1Pic[1];
                    displayBoard[i][2 * j * CHARSIZE + 2] = play1Pic[2];
                }else if (innerBoard[i][j].player == WHITE){
                    displayBoard[i][2 * j * CHARSIZE] = play2Pic[0];
                    displayBoard[i][2 * j * CHARSIZE + 1] = play2Pic[1];
                    displayBoard[i][2 * j * CHARSIZE + 2] = play2Pic[2];
                }
            }else if (innerBoard[i][j].current == YES){        
                if (innerBoard[i][j].player == BLACK){
                    displayBoard[i][2 * j * CHARSIZE] = play1CurrentPic[0];
                    displayBoard[i][2 * j * CHARSIZE + 1] = play1CurrentPic[1];
                    displayBoard[i][2 * j * CHARSIZE + 2] = play1CurrentPic[2];
                }else if (innerBoard[i][j].player == WHITE){
                    displayBoard[i][2 * j * CHARSIZE] = play2CurrentPic[0];
                    displayBoard[i][2 * j * CHARSIZE + 1] = play2CurrentPic[1];
                    displayBoard[i][2 * j * CHARSIZE + 2] = play2CurrentPic[2];
                }
            }
            
        }
    }
}

// 将 innerBoard 中记录的棋子位置，转化到 vBoard 中
void innerBoard2VBoard(int vBoard[SIZE][SIZE]){
    int i, j;
    for (i = 0; i < SIZE; i++){
        for (j = 0; j < SIZE; j++){
            vBoard[i][j] = innerBoard[i][j].player;
        }
    }
}

// 复制虚拟棋盘的副本
void copyBoard(int to[SIZE][SIZE], int from[SIZE][SIZE]){
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            to[i][j] = from[i][j];
        }
    }
}

//显示棋盘格局 
void printDisplayBoard(void){
	int i;
	// 清屏
    int clear = system("clear");  // 清屏

    // 输出提示信息
    if (gameMode == 1){
        printf("    双      人      模      式\n\n");
    }else{
        printf("    人      机      模      式\n\n");
    }
    printf("    本游戏支持一些指令：\n");
    printf("    quit/q -> 回到主页面  regret/r -> 悔棋\n\n");
    
    // 将displayBoard输出到屏幕上
    if (judgeWin() == NOBODY && stepNum < MAXSTEP){
        if (gameMode == 1){
            for (int i = 0; i < SIZE; i++){
                printf("%3d %s          %s\n", SIZE - i, displayBoard[i], DOGE[i]);
            }
        }else{
            for (int i = 0; i < SIZE; i++){
                printf("%3d %s          %s\n", SIZE - i, displayBoard[i], INTELLIGENT_DOGE[i]);
            }
        }
    }else{
        if (judgeWin() != computer && gameMode == 2){
            for (int i = 0; i < SIZE; i++){
                printf("%3d %s          %s\n", SIZE - i, displayBoard[i], FROG[i]);
            }
        }else{
            for (int i = 0; i < SIZE; i++){
                printf("%3d %s          %s\n", SIZE - i, displayBoard[i], GAME_OVER[i]);
            }
        }
    }
    // 输出最下面的一行字母A B ....
    printf("   ");
    for (i = 0; i < SIZE; i++)
        printf("%2c", 'A' + i);
    printf("\n\n");
}