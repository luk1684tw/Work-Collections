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
    chariot_up *ch2;
    chariot_down *ch3;
    chariot_left *ch4;
    int index;
    void chariotaction_left();
    void chariotaction_up();
    void chariotaction_right();
    void chariotaction_down();


private slots:

};

#endif // MAINWINDOW_H
