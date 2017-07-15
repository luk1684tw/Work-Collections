#include "chariot_down.h"
#include "chariot_up.h"
#include "chariot.h"
#include "chariot_left.h"
#include "mainwindow.h"
#include <QPixmap>
#include <QPainter>

chariot_up::chariot_up(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(200,105);
}

void chariot_up::paintEvent(QPaintEvent *)
{
    QPixmap cha;
    QPainter painter(this);
    cha.load(":/Image/chariot_up.png");
    painter.drawPixmap(0,0,100,100,cha);
}
