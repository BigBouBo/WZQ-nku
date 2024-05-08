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


    void paintEvent(QPaintEvent*event);
    //声明
    void initGame();
    void initAIGame();
};
#endif // MAINWINDOW_H
