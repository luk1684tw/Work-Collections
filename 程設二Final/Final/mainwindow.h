#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "chariot.h"
#include "chariot_up.h"
#include "chariot_down.h"
#include "chariot_left.h"
#include "things.h"
#include "easymusic.h"
#include <QMainWindow>
#include <QApplication>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QLabel>
#include <QPushButton>
#include "second.h"
#include <math.h>
#include <ctime>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow(){};
protected:
    void paintEvent(QPaintEvent *);
    void paintEvent_up(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);	//滑鼠點下事件
    void keyPressEvent(QKeyEvent *event);	//鍵盤事件
private:
    chariot *ch1;
    chariot *ch5;
    chariot_up *ch2;
    chariot_up *ch6;
    chariot_down *ch3;
    chariot_down *ch7;
    chariot_left *ch4;
    chariot_left *ch8;
    int index;

    void chariotaction_left();
    void chariotaction_up();
    void chariotaction_right();
    void chariotaction_down();
    void chariotaction_left2();
    void chariotaction_up2();
    void chariotaction_right2();
    void chariotaction_down2();

    QPushButton *button1;
    QPushButton *button2;
    QPushButton *button3;
    QTimer *timer;
    Plane *plane;
    Ball *ball ,*shot;
    second *twoshot;

    Girigiri *giri;
    easyMusic *bgm;
    QTimer *shottimer;
    QTimer *shoottimer;
    Logo *logo;
    void gameSingle();
    void gameDouble();
    void end_animation();

private slots:
    void moveButton1();
    void moveButton2();
    void BallAction();
    void bulletaction();
    void bulletaction1();
};

#endif // MAINWINDOW_H
