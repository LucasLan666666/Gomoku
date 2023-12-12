// 此文件用于游戏过程中处理玩家的输入，以及对字符串的一些操作
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "gomoku.h"

char line[MAXLINE];  //记录读取到的一行

// 自己写的函数，读取一行玩家的输入，从第一个非零字符开始（注意不会读到换行符'\n'）
void mygetline(void){
    int c;
    int i = 0;  // 用于遍历line
    while ((c = getchar()) == ' ')  // 跳过开头的空格
        ;
    while ((i  < MAXLINE - 1) && (c != EOF) && (c != '\n')){
        line[i++] = c;
        c = getchar();
    }
    if (c == EOF){  //读到EOF，退出程序
        int result = system("clear");
        exit(0);
    }else if (c == '\n'){
        line[i] = '\0';
    }else if (i == MAXLINE - 1){
        printf("你的输入过长，请重新输入:\n");
        mygetline();
    }
}

/*
 *  对玩家输入进行判断：
 *      如果输入1，将gameMode设置为1；
 *      如果输入2，将gameMode设置为2；
 *      如果输入的是quit指令，退出游戏；
 *      如果输入有误，返回-1；    
 */
int inputCheckInHomePage(void){
    if (strcmp(line, "1") == 0){
            gameMode = 1;
            printf("你选择了人人对战模式\n");
            printf("是否记录棋谱？（y/n）\n");
            mygetline();            
            isRecord();
            if (gameRecord && readWritePermission){
                createGameRecordFile();
            }else{
                printf("棋谱创建失败，没有足够权限，请尝试在其他目录下执行本程序\n");
            }
    }else if (strcmp(line, "2") == 0){
            gameMode = 2;
            printf("你选择了人机对战模式\n");
            printf("是否记录棋谱？（y/n）\n");
            mygetline();            
            isRecord();
            if (gameRecord && readWritePermission){
                createGameRecordFile();
            }else{
                printf("棋谱创建失败，没有足够权限，请尝试在其他目录下执行本程序\n");
            }
    }else if ((strcmp(line, "quit") == 0) || (strcmp(line, "q") == 0)){
            exit(0);
    }else{
        return -1;
    }
    return 0;
}

/*
 *  对玩家在游戏中输入进行判断：
 *      如果输入的是合法坐标格式，直接完成转换并储存在currentPlayerPlaceStone中，同时返回0；
 *      如果输入的是quit指令，返回1；
 *      如果输入的是regret指令，返回2；
 *      如果输入有误，返回-1
 */
int inputCheckInGame(void){
    if ((strcmp(line, "quit") == 0)|| (strcmp(line, "q") == 0)){
        return 1;
    }else if ((strcmp(line, "regret") == 0)|| (strcmp(line, "r") == 0)){
        return 2;
    }else if (inputToCoordinate() == 0){
        return 0;
    }else {
        return -1;
    }
}