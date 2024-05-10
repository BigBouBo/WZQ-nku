#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gamemodel.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    GameModel *game;
    GameType game_type;//存储游戏类型

    int clickPosRow,clickPosCol;//鼠标轨迹
    bool selectPos = false;//是否选中某个交叉点


    void paintEvent(QPaintEvent*event);
    //声明
    void initGame();
    void initAIGame();

    //鼠标轨迹监听
    void mouseMoveEvent(QMouseEvent *event);
    //鼠标落子
    void mouseReleaseEvent(QMouseEvent *event);

    void chessOneByPerson();
};
#endif // MAINWINDOW_H
