#include "gamemodel.h"
#include<time.h>
#include<stdlib.h>

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

void GameModel::calculateScore()
{
    //统计棋子
    int personNum=0;//人
    int botNum=0;//AI
    int emptyNum=0;//各方向空白格子

    //清空评分
    scoreMapVec.clear();
    for (int i=0;i<BOARD_GRAD_SIZE;i++)
    {
        std::vector<int>lineScores;
        for(int j=0;j<BOARD_GRAD_SIZE;j++)
            lineScores.push_back(0);//清空数组
        scoreMapVec.push_back(lineScores);
    }

    //遍历计分
    for(int row=0;row<BOARD_GRAD_SIZE;row++)
        for(int col=0;col<BOARD_GRAD_SIZE;col++)
        {
            if(row>0 && col>0 && gameMapVec[row][col]==0)//空白点
            {
                //遍历周围八个方向
                for(int y=-1;y<=1;y++)
                    for(int x=-1;x<=1;x++)
                    {
                        personNum=0;
                        botNum=0;
                        emptyNum=0;

                        //原坐标不算
                        if(!(y==0 && x==0))
                        {
                            //对玩家黑子正反两方向评分——防
                            for(int i=1;i<=4;i++)
                            {
                                if(row+i*y>0 && row+i*y<BOARD_GRAD_SIZE &&
                                   col+i*x>0 && col+i*x<BOARD_GRAD_SIZE &&
                                   gameMapVec[row+i*y][col+i*x]==1)//真人玩家的子
                                {
                                    personNum++;
                                }
                                else if(row+i*y>0 && row+i*y<BOARD_GRAD_SIZE &&
                                        col+i*x>0 && col+i*x<BOARD_GRAD_SIZE &&
                                        gameMapVec[row+i*y][col+i*x]==0)//空白格
                                {
                                    emptyNum++;
                                    break;
                                }
                                else//出边界或者AI的子
                                    break;
                            }

                            for(int i=1;i<=4;i++)
                            {
                                if(row-i*y>0 && row-i*y<BOARD_GRAD_SIZE &&
                                   col-i*x>0 && col-i*x<BOARD_GRAD_SIZE &&
                                   gameMapVec[row-i*y][col-i*x]==1)//真人玩家的子
                                {
                                    personNum++;
                                }
                                else if(row-i*y>0 && row-i*y<BOARD_GRAD_SIZE &&
                                        col-i*x>0 && col-i*x<BOARD_GRAD_SIZE &&
                                        gameMapVec[row-i*y][col-i*x]==0)//空白格
                                {
                                    emptyNum++;
                                    break;
                                }
                                else//出边界或者AI的子
                                    break;
                            }

                            if (personNum==1)
                                scoreMapVec[row][col]+=10;
                            else if(personNum==2)
                            {
                                if(emptyNum==1)
                                        scoreMapVec[row][col]+=30;
                                else if(emptyNum==2)
                                        scoreMapVec[row][col]+=40;

                            }
                            else if(personNum==3)
                            {
                              if (emptyNum==1)
                                   scoreMapVec[row][col]+=60;
                              else if(emptyNum==2)
                                   scoreMapVec[row][col]+=110;
                            }
                            else if(personNum==4)
                                scoreMapVec[row][col]+=10100;

                            emptyNum=0;//进行一次清空


                            //对AI白棋正反两方向进行评分———攻
                            for(int i=1;i<=4;i++)
                            {
                                if(row+i*y>0 && row+i*y<BOARD_GRAD_SIZE &&
                                   col+i*x>0 && col+i*x<BOARD_GRAD_SIZE &&
                                   gameMapVec[row+i*y][col+i*x]==-1)//真人玩家的子
                                {
                                    botNum++;
                                }
                                else if(row+i*y>0 && row+i*y<BOARD_GRAD_SIZE &&
                                        col+i*x>0 && col+i*x<BOARD_GRAD_SIZE &&
                                        gameMapVec[row+i*y][col+i*x]==0)//空白格
                                {
                                    emptyNum++;
                                    break;
                                }
                                else//出边界或者AI的子
                                    break;
                            }

                            for(int i=1;i<=4;i++)
                            {
                                if(row-i*y>0 && row-i*y<BOARD_GRAD_SIZE &&
                                   col-i*x>0 && col-i*x<BOARD_GRAD_SIZE &&
                                   gameMapVec[row-i*y][col-i*x]==-1)//真人玩家的子
                                {
                                    botNum++;
                                }
                                else if(row-i*y>0 && row-i*y<BOARD_GRAD_SIZE &&
                                        col-i*x>0 && col-i*x<BOARD_GRAD_SIZE &&
                                        gameMapVec[row-i*y][col-i*x]==0)//空白格
                                {
                                    emptyNum++;
                                    break;
                                }
                                else//出边界或者AI的子
                                    break;
                            }


                            if(botNum==0)
                                scoreMapVec[row][col]+=5;
                            else if (botNum==1)
                                scoreMapVec[row][col]+=10;
                            else if(botNum==2)
                            {
                                if(emptyNum==1)
                                        scoreMapVec[row][col]+=25;
                                else if(emptyNum==2)
                                        scoreMapVec[row][col]+=50;

                            }
                            else if(botNum==3)
                            {
                              if (emptyNum==1)
                                   scoreMapVec[row][col]+=55;
                              else if(emptyNum==2)
                                   scoreMapVec[row][col]+=100;
                            }
                            else if(botNum>=4)
                                scoreMapVec[row][col]+=20000;


                        }
                    }

             }
        }
}

void GameModel::actionByAI(int &clickRow, int clickCol)
{
    calculateScore();

    int maxScore=0;
    std::vector<std::pair<int,int>>maxPoints;

    for(int row=1;row<BOARD_GRAD_SIZE;row++)
        for (int col=1;col<BOARD_GRAD_SIZE;col++)
    {
        if (gameMapVec[row][col]==0)
        {
           if(scoreMapVec[row][col]>maxScore)
           {
               maxPoints.clear();
               maxScore=scoreMapVec[row][col];
               maxPoints.push_back(std::make_pair(row,col));
           }
           else if (scoreMapVec[row][col]==maxScore)
           {
              maxPoints.push_back(std::make_pair(row,col));
           }
        }
    }

    //多个点时随机落子
    srand((unsigned)time(0));
    int index=rand()%maxPoints.size();

    std::pair<int,int>pointPair=maxPoints.at(index);
    clickRow=pointPair.first;
    clickCol=pointPair.second;

    updateGameMap(clickRow,clickCol);

}



