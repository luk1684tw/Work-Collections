#include "chariot_down.h"
#include "chariot_up.h"
#include "chariot.h"
#include "chariot_left.h"
#include "mainwindow.h"
#include <QPixmap>
#include <QPainter>

chariot_left::chariot_left(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(200,105);
}

void chariot_left::paintEvent(QPaintEvent *)
{
    QPixmap cha;
    QPainter painter(this);
    cha.load(":/Image/chariot_left.png");
    painter.drawPixmap(0,0,100,100,cha);
}

