#include "gamemodel.h"

void GameModel::startGame(GameType type)
{
    gameType =type;

    //初始棋盘
    gameMapVec.clear();
    for(int i=0;i<BOARD_GRAD_SIZE;i++)
    {
        std::vector<int>lineBoard;
        for(int j=0;j<BOARD_GRAD_SIZE;j++)
            lineBoard.push_back(0);
        gameMapVec.push_back(lineBoard);

    }

    //积分
    if (gameType==AI)
    {
        scoreMapVec.clear();
        for(int i=0;i<BOARD_GRAD_SIZE;i++)
        {
            std::vector<int>lineScores;
            for(int j=0;j<BOARD_GRAD_SIZE;j++)
                lineScores.push_back(0);
            gameMapVec.push_back(lineScores);
        }
    }

    //轮到黑棋true，白棋false
    playerFlag=true;

}

void GameModel::actionByPerson(int row, int col)
{
    updateGameMap(row,col);
}


void GameModel::updateGameMap(int row, int col)
{
    if(playerFlag)
        gameMapVec[row][col]=1;
    else
        gameMapVec[row][col]=-1;

    //换手
    playerFlag= !playerFlag;
}

//判断是否赢了
bool GameModel::isWin(int row, int col)
{
    //水平方向
    for (int i=0;i<5;i++)
    {
        if (col-i>0 && col-i+4<BOARD_GRAD_SIZE &&
                gameMapVec[row][col-i]==gameMapVec[row][col-i+1] &&
                gameMapVec[row][col-i]==gameMapVec[row][col-i+2] &&
                gameMapVec[row][col-i]==gameMapVec[row][col-i+3] &&
                gameMapVec[row][col-i]==gameMapVec[row][col-i+4])
            return true;
    }

    //竖直方向
    for (int i=0;i<5;i++)
    {
        if (row-i>0 && row-i+4<BOARD_GRAD_SIZE &&
                gameMapVec[row-i][col]==gameMapVec[row-i+1][col] &&
                gameMapVec[row-i][col]==gameMapVec[row-i+2][col] &&
                gameMapVec[row-i][col]==gameMapVec[row-i+3][col] &&
                gameMapVec[row-i][col]==gameMapVec[row-i+4][col] )
            return true;
    }

    //斜着的“/”
    for (int i=0;i<5;i++)
    {
        if (row+i<BOARD_GRAD_SIZE && row+i-4>0 && col-i>0 && col-i+4<BOARD_GRAD_SIZE &&
                gameMapVec[row+i][col-i]==gameMapVec[row+i-1][col-i+1] &&
                gameMapVec[row+i][col-i]==gameMapVec[row+i-2][col-i+2] &&
                gameMapVec[row+i][col-i]==gameMapVec[row+i-3][col-i+3] &&
                gameMapVec[row+i][col-i]==gameMapVec[row+i-4][col-i+4] )
            return true;
    }

    //斜着的"\"
    for (int i=0;i<5;i++)
    {
        if (row-i>0 && row-i+4<BOARD_GRAD_SIZE && col-i>0 && col-i+4<BOARD_GRAD_SIZE &&
                gameMapVec[row-i][col-i]==gameMapVec[row-i+1][col-i+1] &&
                gameMapVec[row-i][col-i]==gameMapVec[row-i+2][col-i+2] &&
                gameMapVec[row-i][col-i]==gameMapVec[row-i+3][col-i+3] &&
                gameMapVec[row-i][col-i]==gameMapVec[row-i+4][col-i+4])
            return true;
     }
    return false;
}

