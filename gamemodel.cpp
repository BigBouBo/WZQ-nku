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
