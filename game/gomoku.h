// 头文件，包含了一些常量定义和函数声明
#ifndef GOMOKU_H
#define GOMOKU_H
#define SIZE 15  // 棋盘大小
#define CHARSIZE 3  // 棋盘使用的是UTF8编码，每一个中文字符占用3个字节
#define MAXLINE 50  // 定义玩家输入的最大长度
#define NAMESIZE 20  // 定义玩家输入的名字的最大长度

// 字符艺术
extern const char* HAPPY_GOMOKU[];
extern const char* FROG[];
extern const char* DOGE[];
extern const char* GAME_OVER[];

extern int gameMode;  // 游戏模式，1表示双人对战，2表示人机对战，3表示读取棋谱，4表示退出游戏，-1表示输入有误

extern int gameRecord;  // 是否开启记谱模式，1为是，0为否
extern int readWritePermission;  // 是否有读写权限，1为是，0为否
extern char roundName[NAMESIZE + 6];  // 游戏对局名称
extern char pathOfRound[NAMESIZE + 22];  // 游戏对局的路径

// 用于记录玩家落子的坐标
struct placeStone{
    int x;
    int y;
};

extern int stepNum;  // 记录当前步数
extern struct placeStone stepRecord[225];  // 记录每一步的下棋内容，stepRecord[0]为第一步，stepRecord[1]为第二步，以此类推


// 空棋盘模板
extern char arrayForEmptyBoard[SIZE][(2 * SIZE - 1) * CHARSIZE + 1];

// 以下是棋子的图案
extern char play1Pic[];  // 黑棋子
extern char play1CurrentPic[]; // 黑棋子的当前落子位置
extern char play2Pic[];  // 白棋子
extern char play2CurrentPic[]; // 白棋子的当前落子位置

// 当前的棋盘的格局 
extern int arrayForInnerBoardLayout[SIZE][SIZE];

// 显示的棋盘 
extern char arrayForDisplayBoard[SIZE][(2 * SIZE - 1) * CHARSIZE + 1];

// 用于记录棋盘上面一个子的各方面信息
struct stoneState{
    int x;  // 横坐标
    int y;  // 纵坐标
    int player;  // 玩家，1表示黑方，2表示白方
    int N, NE, E, SE, S, SW, W, NW;  // 8个方向的连子数（不包含自身）
    int step;  // 步数
};

// 当前等待落子的玩家，1表示黑方，2表示白方
extern int player;

// 记录读取到的一行
extern char line[];

void homePage(void);  // 初始化整个游戏，回到主页面，根据玩家输入确定游戏模式，读到quit或者q时退出游戏
void End(void);  // 直接清屏退出游戏

void playerVsPlayer(void);  // 人人对战模式
void regret1(void);  // 人人对战模式的悔棋模式

void playerVsComputer(void);  // 人机对战模式
void regret2(void);  // 人机对战模式的悔棋模式

// 初始化一个空棋盘格局
void initRecordBoard(void);

//将arrayForInnerBoardLayout中记录的棋子位置，转化到arrayForDisplayBoard中
void innerLayoutToDisplayArray(void);

//显示棋盘格局以及其他有关信息
void displayBoard(void);

// 自己写的函数，读取一行玩家的输入，从第一个非零字符开始（注意不会读到换行符'\n'）
void mygetline(void);

/*
 *  对玩家输入进行判断：
 *      如果输入1，返回1；
 *      如果输入2，返回2；
 *      如果输入3，返回3；
 *      如果输入quit指令，返回4；
 *      如果输入有误，返回-1；    
 */
int inputCheckInHomePage(void);

/*
 *  对玩家在游戏中输入进行判断：
 *      如果输入的是合法坐标格式，直接完成转换并储存在stepRecord[stepNum]中，同时返回0；
 *      如果输入的是quit指令，返回1；
 *      如果输入的是regret指令，返回2；
 *      如果输入有误，返回-1
 */
int inputCheckInGame(void);

// 将玩家的输入转化为坐标，若为合法坐标，则返回0，否则返回-1
int inputToCoordinate(void);

// 将玩家当前输入的坐标转化为棋盘上的落子
void coordinateToPlaceStone(void);

// 从键盘读取输入判断是否开启记谱模式，y为是，n为否，并将结果记录在gameRecord和readWritePermission中
void isRecord(void);

// 判断当前目录下是否有读写权限，有则返回1，没有返回0
int isReadWritePermission(void);

// 判断文件是否存在，存在返回1，不存在返回0
int isFileExist(const char *filename);

// 创立棋谱文件,询问玩家如何起名，将棋谱文件命名为玩家输入的名字，否则默认为对局开始时间
void createGameRecordFile(void);

// 记录棋谱到本地
void recordGameRoundToLocal(void);

// 读取棋谱    
void readGameRecord(void);

// 判断是否有胜者出现：若黑棋获胜，返回1；白棋获胜，返回2；未出现胜者，返回0
int judgeWin(void);

#endif