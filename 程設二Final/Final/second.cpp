#include "second.h"
#include <QPainter>
#include <QPixmap>


second::second(QWidget *parent) : QWidget(parent)
{
    setFixedSize(20,20);
}

void second::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":Image/2pdot.png");
    painter.drawPixmap(0,0,20,20,pix);
}
