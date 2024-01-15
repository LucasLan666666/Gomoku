// 此文件用于实现游戏对局的记录
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include "../gomoku.h"

int gameRecord; // 是否开启记谱模式
int readWritePermission; // 是否有读写权限
char roundName[NAMESIZE + 6]; // 游戏对局名称
char pathOfRound[NAMESIZE + 22]; // 游戏对局的路径
int stepNum; // 记录当前步数
Coordinate stepRecord[MAXSTEP]; // 记录每一步的下棋内容，stepRecord [0] 为第一步，stepRecord [1] 为第二步，以此类推
char stepName[13]; // 记录下棋内容的字符串

// 从键盘读取输入判断是否开启记谱模式，1 为是，2 为否，并将结果记录在 gameRecord 和 readWritePermission中
void isRecord(void) {
    printf("是否记录棋谱？（1：是 2：否）");
    mygetline(line);            
    while (1) {
        if (strcmp(line, "1") == 0) {
            gameRecord = YES;
            break;
        } else if (strcmp(line, "2") == 0) { 
            gameRecord = NO;
            break;
        } else {
            printf("您的输入有误，请重新输入：");
            mygetline(line);
        }
    }

    if (gameRecord) {
        readWritePermission = isReadWritePermission();
    }
}

// 判断当前目录下是否有读写权限，有则返回 1，没有返回 0
int isReadWritePermission(void) {
    if (access(".", R_OK | W_OK) == 0) {
        return YES;
    } else {
        return NO;
    }
}

// 判断文件是否存在，存在返回 1，不存在返回 0
int isFileExist(const char *filename) {
    return access(filename, F_OK) != -1;
}

// 创立棋谱文件,询问玩家如何起名，将棋谱文件命名为玩家输入的名字，否则默认为对局开始时间
void createGameRecordFile(void) {
    char localTime[NAMESIZE]; // 用于储存对局开始时间
    // 先创建棋谱文件夹
    #ifdef _WIN32  // 如果是 Windows 系统
        mkdir("game_record");
    #else  // 如果是 Unix-like 系统
        mkdir("game_record", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    #endif

    printf("请为棋谱文件命名(不需要额外添加后缀名，若没有检测到有效输入，默认以对局开始时间命名)：");
    mygetline(line);
    while (strlen(line) > NAMESIZE) {
        printf("您的输入过长，请重新输入：");
        mygetline(line);
    }

   // 获取当前时间
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
        strftime(localTime, NAMESIZE, "%Y-%m-%d_%H-%M-%S", t);
    
   // 针对玩家输入创建文件
    while (1) {
        if (strcmp(line, "") == 0) { // 玩家输入空字符，用时间命名
        sprintf(roundName, "%s%s", "Game-", localTime); // 将时间转化为字符串
        } else {
            strcpy(roundName, line); // 用玩家输入命名
        }
        sprintf(pathOfRound, "%s/%s.txt", "game_record", roundName); // 生成路径名
        if ((isFileExist(pathOfRound)) == 0) {
            break;
        }
        printf("文件已存在，请重新输入：");
        mygetline(line);
    }
    
   // 修改时间打入棋谱的格式
    strftime(localTime, NAMESIZE, "%Y/%m/%d %H:%M:%S", t);
    
   // 创建文件
    FILE *fp = fopen(pathOfRound, "w"); // 创建文件
   // 写入文件
    fprintf(fp, "# Round Name:  %s\n", roundName);
    fprintf(fp, "# Round Time:  %s\n", localTime);
    fprintf(fp, "# Game Mode(1 for pvp while -1 for pve):\n");
    fprintf(fp,"  %d\n", gameMode);
    if (gameMode == 2) {
        fprintf(fp, "# Player Color(1 for BLACK while 2 for WHITE):\n");
        fprintf(fp,"  %d\n", (computer == BLACK) ? WHITE : BLACK);
    }
    fprintf(fp, "# Record?(1 for yes, 2 for no)\n");
    fprintf(fp,"  2\n");
    fprintf(fp, "# Game Record:\n");
   // 关闭文件
    fclose(fp);
}

// 记录棋谱到本地
void recordGameRoundToLocal(void) {
    FILE *fp = fopen(pathOfRound, "a");
   // 写入文件
    sprintf(stepName, "%c%d", stepRecord[stepNum].y + 'A', SIZE - stepRecord[stepNum].x); // 将坐标转化为字符串，储存在stepName中
    if (gameMode == 2 && player == computer) {
        fprintf(fp, "# ");
    } else {
        fprintf(fp, "  ");
    }
    fprintf(fp, "%s\n", stepName);
   // 关闭文件
    fclose(fp);
}

void saveRegretToLocal(void) {
    FILE *fp = fopen(pathOfRound, "a");
   // 写入文件
    fprintf(fp, "  regret\n");
   // 关闭文件
    fclose(fp);
}
