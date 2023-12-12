// 头文件，包含了一些常量定义和函数声明
#define SIZE 15  // 棋盘大小
#define CHARSIZE 3  // 棋盘使用的是UTF8编码，每一个中文字符占用3个字节
#define MAXLINE 50  // 定义玩家输入的最大长度
#define NAMESIZE 20 // 定义玩家输入的名字的最大长度

// 字符艺术
extern const char* HAPPY_GOMOKU[];
extern const char* FROG[];
extern const char* DOGE[];
extern const char* GAME_OVER[];

// 游戏模式，1表示双人对战，2表示人机对战
extern int gameMode;

// 是否开启记谱模式，1为是，0为否
extern int gameRecord;
// 是否有读写权限，1为是，0为否
extern int readWritePermission;
// 游戏对局名称
extern char roundName[NAMESIZE + 6];
// 游戏对局的路径
extern char pathOfRound[NAMESIZE + 22];
// 记录当前步数
extern int stepNum;

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

struct placeStone{
    int x;
    int y;
};
// 上一步玩家落子的坐标
extern struct placeStone lastPlayerPlaceStone;
// 当前玩家落子的坐标
extern struct placeStone currentPlayerPlaceStone;

// 当前等待落子的玩家，1表示黑方，2表示白方
extern int player;

// 记录读取到的一行
extern char line[];

// 初始化整个游戏，回到主页面
void homePage(void);

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

// 自己写的函数，读取一行玩家的输入，从第一个非零字符开始（注意不会读到换行符'\n'）
void mygetline(void);

/*
 *  对玩家输入进行判断：
 *      如果输入1，将gameMode设置为1；
 *      如果输入2，将gameMode设置为2；
 *      如果输入的是quit指令，退出游戏；
 *      如果输入有误，返回-1
 */
int inputCheckInHomePage(void);
/*
 *  对玩家在游戏中输入进行判断：
 *      如果输入的是合法坐标格式，直接完成转换并储存在currentPlayerPlaceStone中，同时返回0；
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

// 创立棋谱文件,询问玩家如何起名，，将棋谱文件命名为玩家输入的名字，否则默认为对局开始时间
void createGameRecordFile(void);

// 记录棋谱到本地
void recordGameRoundToLocal(void);

// 判断是否有胜者出现：若黑棋获胜，返回1；白棋获胜，返回2；未出现胜者，返回0
int judgeWin(void);