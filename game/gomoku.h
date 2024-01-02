// 头文件，包含了一些常量定义和函数声明
#ifndef GOMOKU_H
#define GOMOKU_H
#define SIZE 15  // 棋盘大小
#define CHARSIZE 3  // 棋盘使用的是UTF8编码，每一个中文字符占用3个字节
#define MAXLINE 50  // 定义玩家输入的最大长度
#define NAMESIZE 20  // 定义玩家输入的名字的最大长度
#define MAXSTEP SIZE*SIZE  // 定义最大步数
#define BLACK 1  // 定义黑方
#define WHITE 2  // 定义白方
#define NOBODY 0  // 定义没有人
#define YES 1  // 定义是
#define NO 0  // 定义否

// 用于记录棋盘上面一个子的信息
struct stone{
    int current;  // 0 表示不是当前落子目标，1 表示是当前落子目标
    int player;  // 玩家，BLACK 表示黑方，WHITE 表示白方, NOBODY表示没有棋子
    int direction[8];  // 8 个方向与自己同色的连子数（不包含自身），只统计最多四个连子的情况，北方为零号元素，顺时针方向依次为 1，2，3，4，5，6，7
};

// 用于记录玩家落子的坐标
struct placeStone{
    int x;
    int y;
};

// 字符艺术
extern const char* HAPPY_GOMOKU[];
extern const char* FROG[];
extern const char* DOGE[];
extern const char* INTELLIGENT_DOGE[];
extern const char* GAME_OVER[];

extern int gameMode;  // 游戏模式，1 表示双人对战，2 表示人机对战，3 表示退出游戏，-1表示输入有误
extern int computer;  // 电脑执子，BLACK 为黑子，WHITE 为白子

extern int gameRecord;  // 是否开启记谱模式，1为是，0为否
extern int readWritePermission;  // 是否有读写权限，1为是，0为否
extern char roundName[NAMESIZE + 6];  // 游戏对局名称
extern char pathOfRound[NAMESIZE + 22];  // 游戏对局的路径

extern int stepNum;  // 记录当前步数
extern struct placeStone stepRecord[];  // 记录每一步的下棋内容，stepRecord[0] 为第一步，stepRecord[1] 为第二步，以此类推
extern char stepName[];  // 记录下棋内容的字符串

// 空棋盘模板
extern char arrayForEmptyBoard[SIZE][(2 * SIZE - 1) * CHARSIZE + 1];

// 以下是棋子的图案
extern char play1Pic[];  // 黑棋子
extern char play1CurrentPic[]; // 黑棋子的当前落子位置
extern char play2Pic[];  // 白棋子
extern char play2CurrentPic[]; // 白棋子的当前落子位置

// 当前的棋盘的格局 
extern struct stone arrayForInnerBoardLayout[SIZE][SIZE];

// 显示的棋盘 
extern char arrayForDisplayBoard[SIZE][(2 * SIZE - 1) * CHARSIZE + 1];

// 当前等待落子的玩家，BLACK 表示黑方，WHITE 表示白方
extern int player;

// 记录读取到的一行
extern char line[];

void homePage(void);  // 初始化整个游戏，回到主页面，根据玩家输入确定游戏模式，读到 quit 或者 q 时退出游戏
void whoGoFirst(void); // 提示玩家输入自己执子的颜色，并修改 computer 的值
void End(void);  // 直接清屏退出游戏

void playerVsPlayer(void);  // 人人对战模式
void regret1(void);  // 人人对战模式的悔棋模式

void playerVsComputer(void);  // 人机对战模式
void regret2(void);  // 人机对战模式的悔棋模式

// 初始化一个空棋盘格局
void initRecordBoard(void);

//将 arrayForInnerBoardLayout 中记录的棋子位置，转化到 arrayForDisplayBoard 中
void innerLayoutToDisplayArray(void);

//显示棋盘格局以及其他有关信息
void displayBoard(void);

// 自己写的函数，读取一行玩家的输入，从第一个非零字符开始（注意不会读到换行符'\n'）
void mygetline(void);

/*
 *  对玩家输入进行判断：
 *      如果输入 1，返回 1；
 *      如果输入 2，返回 2；
 *      如果输入 quit 指令，返回 3；
 *      如果输入有误，返回 -1；    
 */
int inputCheckInHomePage(void);

/*
 *  对玩家在游戏中输入进行判断：
 *      如果输入的是合法坐标格式，直接完成转换并储存在 stepRecord[stepNum] 中，同时返回 0；
 *      如果输入的是 quit 指令，返回 1；
 *      如果输入的是 regret 指令，返回 2；
 *      如果输入有误，返回 -1
 */
int inputCheckInGame(void);

// 将玩家的输入转化为坐标，若为合法坐标，则返回 0，否则返回 -1
int inputToCoordinate(void);

// 将玩家当前输入的坐标转化为棋盘上的落子，并更新棋子的状态
void coordinateToPlaceStone(void);

// 从键盘读取输入判断是否开启记谱模式，y 为是，n 为否，并将结果记录在 gameRecord 和 readWritePermission 中
void isRecord(void);

// 判断当前目录下是否有读写权限，有则返回 1，没有返回 0
int isReadWritePermission(void);

// 判断文件是否存在，存在返回 1，不存在返回 0
int isFileExist(const char *filename);

// 创立棋谱文件,询问玩家如何起名，将棋谱文件命名为玩家输入的名字，否则默认为对局开始时间
void createGameRecordFile(void);

// 记录棋谱到本地
void recordGameRoundToLocal(void);

// 删除棋谱中的最后一步
void saveRegretToLocal(void);

// 判断是否有胜者出现：若黑棋获胜，返回 1；白棋获胜，返回 2；未出现胜者，返回 0
int judgeWin(void);

#endif