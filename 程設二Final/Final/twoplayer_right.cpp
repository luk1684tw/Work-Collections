#include "twoplayer_up.h"
#include "twoplayer_down.h"
#include "twoplayer_left.h"
#include "twoplayer_right.h"
#include "mainwindow.h"
#include <QPixmap>
#include <QPainter>


twoplayer_right::twoplayer_right(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(200,105);
}

void twoplayer_right::paintEvent(QPaintEvent *)
{
    QPixmap cha;
    QPainter painter(this);
    cha.load(":/Image/chariot.png");
    painter.drawPixmap(0,0,600,100,cha);
}
