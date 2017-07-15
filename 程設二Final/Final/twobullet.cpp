#include "twobullet.h"
#include <QPainter>
#include <QPixmap>


twobullet::twobullet(QWidget *parent):QWidget(parent)
{
    this->setFixedSize(20,20);
}
twobullet::~twobullet()
{

}

void twobullet::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/Image/2pdot.png");
    painter.drawPixmap(0,0,20,20,pix);
}
