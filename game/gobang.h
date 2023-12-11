// 头文件，包含了一些常量定义和函数声明
#include "macro.h"

// 游戏模式，1表示双人对战，2表示人机对战
extern int mode;

// 空棋盘模板
extern char arrayForEmptyBoard[SIZE][SIZE*CHARSIZE+1];

// 以下是棋子的图案
extern char play1Pic[];  // 黑棋子
extern char play1CurrentPic[]; // 黑棋子的当前落子位置
extern char play2Pic[];  // 白棋子
extern char play2CurrentPic[]; // 白棋子的当前落子位置

// 当前的棋盘的格局 
extern int arrayForInnerBoardLayout[SIZE][SIZE];

// 显示的棋盘 
extern char arrayForDisplayBoard[SIZE][SIZE*CHARSIZE+1];

// 上一步玩家落子的坐标
extern int lastPlayerMoveStone[];
// 当前玩家落子的坐标
extern int currentPlayerMoveStone[];

// 当前等待落子的玩家，1表示黑方，2表示白方
extern int player;

// 记录读取到的一行
extern char line[];

// 初始化整个游戏，回到主页面
void initGame(void);

// 人人对战模式
void playerVsPlayer(void);
// 人人对战模式的悔棋模式
void regret1(void);

// 人机对战模式
void playerVsComputer(void);
// 人机对战模式的悔棋模式
void regret2(void);

// 初始化一个空棋盘格局
void initRecordBoard(void);

//将arrayForInnerBoardLayout中记录的棋子位置，转化到arrayForDisplayBoard中
void innerLayoutToDisplayArray(void);

//显示棋盘格局以及其他有关信息
void displayBoard(void);

// 读取一行玩家的输入
void mygetline(char s[], int lim);
// 比较两个字符串，1表示二者相同，0表示二者不同
int mystrcmp(char *s, char *t);


// 对玩家输入进行判断：如果输入的是坐标，直接修改currentPlayerMoveStone[2]并返回0；如果输入的是quit指令，返回1；如果输入的是regret指令，返回2；如果输入有误，返回-1
int inputCheck(void);

// 将玩家的输入转化为坐标，若为合法坐标，则返回0，否则返回-1
int inputToCoordinate(void);

// 将玩家当前输入的坐标转化为棋盘上的落子
void coordinateToMoveStone(void);