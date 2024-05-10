#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <vector>

//游戏类型
enum GameType
{
    MAN,
    AI
};

//游戏状态
enum GameStatus
{
    PLAYING,
    WIN,
    DEAD
};

const int BOARD_GRAD_SIZE=15;//棋盘尺寸

const int MARGIN=30;//棋盘边缘空隙
const int CHESS_RADIUS=15;
const int MARK_SIZE=6;
const int BLOCK_SIZE=40;//方格大小
const int POS_OFFSET=BLOCK_SIZE*0.4;//鼠标靠近的模糊距离
const int AI_THINK_TIME=700;

class GameModel
{
public:
    GameModel(){};

public:
    //存储当前情况，空白为0，黑子1，白子-1
    std::vector<std::vector<int>>gameMapVec;

    //存储当前情况，空白为0，黑子1，白子-1
    std::vector<std::vector<int>>scoreMapVec;

    //标示下棋方，true：黑棋 false:AI 白棋
    bool playerFlag;

    GameType gameType;//游戏模式
    GameStatus gameStatus;//状态

    void startGame(GameType type);
    void calculateScore();
    void actionByPerson(int row,int col);
    void actionByAI(int &clickRow,int clickCol);
    void updateGameMap(int row,int col);
    bool isWin(int row,int col);
    bool isDeadGame();
};




#endif // GAMEMODEL_H
