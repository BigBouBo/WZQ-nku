#include "mainwindow.h"
#include "ui_mainwindow.h"


#include<QPainter>
#include<QMouseEvent>
#include<QMessageBox>
#include<math.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setMouseTracking(true);

    //设置窗口大小
    setFixedSize(MARGIN*2+BLOCK_SIZE*BOARD_GRAD_SIZE,
                 MARGIN*2+BLOCK_SIZE*BOARD_GRAD_SIZE);

    initGame();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //22没调用抗锯齿最后可以加上

    //绘制棋盘
    for (int i=0;i<BOARD_GRAD_SIZE+1;i++)
    {//竖线左到右
        painter.drawLine(MARGIN+BLOCK_SIZE*i,MARGIN,
                         MARGIN+BLOCK_SIZE*i,size().height()-MARGIN);
     //横线上到下
        painter.drawLine(MARGIN,MARGIN+BLOCK_SIZE*i,
                         size().width()-MARGIN,MARGIN+BLOCK_SIZE*i);
    }

    //绘制选中点
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);

    //绘制骡子标记
    if (clickPosRow>0 && clickPosRow<BOARD_GRAD_SIZE && clickPosCol>0 && clickPosCol<BOARD_GRAD_SIZE &&
            game ->gameMapVec[clickPosRow][clickPosCol]==0)
    {
        if (game->playerFlag)
            brush.setColor(Qt::black);
        else
            brush.setColor(Qt::white);
        painter.setBrush(brush);
        painter.drawEllipse(MARGIN + BLOCK_SIZE * clickPosCol - MARK_SIZE/2,MARGIN + BLOCK_SIZE * clickPosRow - MARK_SIZE/2,10,10);
    }

    //绘制棋子
    for (int i=0;i<BOARD_GRAD_SIZE;i++)
        for (int j=0;j<BOARD_GRAD_SIZE;j++)
      {
       {
         if(game->gameMapVec[i][j]==1)
         {
             brush.setColor(Qt::black);

             painter.setBrush(brush);
             painter.drawEllipse(MARGIN+BLOCK_SIZE*j-CHESS_RADIUS,MARGIN+BLOCK_SIZE*i-CHESS_RADIUS,30,30);
         }
         else if(game->gameMapVec[i][j]==-1)
         {
             brush.setColor(Qt::white);

             painter.setBrush(brush);
             painter.drawEllipse(MARGIN+BLOCK_SIZE*j-CHESS_RADIUS,MARGIN+BLOCK_SIZE*i-CHESS_RADIUS,30,30);//qt画椭圆
          }
        }
     }


    //判断输赢
    if (clickPosRow>0 && clickPosRow<BOARD_GRAD_SIZE &&
        clickPosCol>0 && clickPosCol<BOARD_GRAD_SIZE &&
       (game ->gameMapVec[clickPosRow][clickPosCol]==1 ||game ->gameMapVec[clickPosRow][clickPosCol]==-1))
    {
        if(game->isWin(clickPosRow,clickPosCol) && game->gameStatus==PLAYING)
        {
         game->gameStatus=WIN;
         QString str;
         if (game->gameMapVec[clickPosRow][clickPosCol]==1)
             str="黑棋";
         else if (game->gameMapVec[clickPosRow][clickPosCol]==-1)
             str="白棋";
         QMessageBox::StandardButton btnValue = QMessageBox::information(this,"南开五子棋大对决",str+"赢啦！！");

         //重置游戏状态
         if(btnValue==QMessageBox::Ok)
         {
             game->startGame(game_type);
             game->gameStatus=PLAYING;
         }
        }
    }

}

void MainWindow::initGame()
{
    //初始化模型
    game=new GameModel;
    initAIGame();
}

void MainWindow::initAIGame()
{
    game_type=AI;
    game->gameStatus = PLAYING;

    //在数据模型中进行初始化
    game->startGame(game_type);
            update();
}

//鼠标落子轨迹监听，移动就调用
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    //通过鼠标确定落子标记
    int x =event->x();
    int y =event->y();

    if(x >= MARGIN+BLOCK_SIZE/2 &&
       x < size().width()-MARGIN-BLOCK_SIZE/2 &&
       y >= MARGIN+BLOCK_SIZE/2 &&
       y < size().width()-MARGIN-BLOCK_SIZE/2 )
     {
        int col = (x-MARGIN)/BLOCK_SIZE;
        int row = (y-MARGIN)/BLOCK_SIZE;

        int leftTopPosX = MARGIN + BLOCK_SIZE*col;
        int leftTopPosY = MARGIN + BLOCK_SIZE*row;

        //根据距离选最近的交叉点
        clickPosRow = -1;//初始化最终值
        clickPosCol = -1;
        int len = 0;//计算完取整

        selectPos = false;//选取是否成功

        //确定唯一在误差内的点
        len=sqrt((x-leftTopPosX)*(x-leftTopPosX)+(y-leftTopPosY)*(y-leftTopPosY));
        if(len < POS_OFFSET)
        {
            clickPosRow = row;
            clickPosCol = col;
            if (game->gameMapVec[clickPosRow][clickPosCol]==0)//选中的地方没有棋子
            {
                selectPos = true;
            }
        }

        len=sqrt((x-leftTopPosX-BLOCK_SIZE)*(x-leftTopPosX-BLOCK_SIZE)+(y-leftTopPosY)*(y-leftTopPosY));
        if(len < POS_OFFSET)
        {
            clickPosRow = row;
            clickPosCol = col + 1;
            if (game->gameMapVec[clickPosRow][clickPosCol]==0)//选中的地方没有棋子
            {
                selectPos = true;
            }
        }

        len=sqrt((x-leftTopPosX)*(x-leftTopPosX)+(y-leftTopPosY-BLOCK_SIZE)*(y-leftTopPosY-BLOCK_SIZE));
        if(len < POS_OFFSET)
        {
            clickPosRow = row + 1;
            clickPosCol = col;
            if (game->gameMapVec[clickPosRow][clickPosCol]==0)//选中的地方没有棋子
            {
                selectPos = true;
            }
        }

        len=sqrt((x-leftTopPosX-BLOCK_SIZE)*(x-leftTopPosX-BLOCK_SIZE)+(y-leftTopPosY-BLOCK_SIZE)*(y-leftTopPosY-BLOCK_SIZE));
        if(len < POS_OFFSET)
        {
            clickPosRow = row + 1;
            clickPosCol = col + 1;
            if (game->gameMapVec[clickPosRow][clickPosCol]==0)//选中的地方没有棋子
            {
                selectPos = true;
            }
        }

    }
    update();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
   if(selectPos == false){
       return;
   }
   else{
       selectPos = false;
   }

   chessOneByPerson();

   if (game_type== AI){

   }
}

void MainWindow::chessOneByPerson(){
    //这里没子
    if(clickPosRow!=-1 && clickPosCol !=-1 && game->gameMapVec[clickPosRow][clickPosCol]==0)
    {
        game->actionByPerson(clickPosRow,clickPosCol);


        update();
    }
}

