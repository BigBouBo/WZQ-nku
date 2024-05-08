#include "mainwindow.h"
#include "ui_mainwindow.h"


#include<QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
