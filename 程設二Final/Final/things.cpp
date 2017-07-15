#include "things.h"
#include <QPainter>
#include <QPixmap>

Plane::Plane(QWidget *parent): QWidget(parent)
{
    this->setFixedSize(100,75);
}
Plane::~Plane()
{

}

void Plane::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/Image/plane.png");
    painter.drawPixmap(0,0,50,50,pix);

}
Ball::Ball(QWidget *parent):QWidget(parent)
{
    this->setFixedSize(20,20);
}
Ball::~Ball()
{

}

void Ball::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/Image/ball.png");
    painter.drawPixmap(0,0,20,20,pix);
}
Bang::Bang(QWidget *parent):QWidget(parent)
{
    this->setFixedSize(300,300);
    src[0]=":/Image/bang.png";
    src[1]=":/Image/bang1.png";
}
Bang::~Bang()
{

}
void Bang::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    if(i){
        pix.load(src[i]);
        i=0;
    }else{
        pix.load(src[i]);
        i=1;
    }
    painter.drawPixmap(0,0,300,300,pix);
}
Girigiri::Girigiri(QWidget *parent):QWidget(parent)
{
    this->setFixedSize(850,550);
    src[0]=":/Image/1.jpg";
    src[1]=":/Image/2.jpg";
    src[2]=":/Image/3.jpg";
    src[3]=":/Image/4.jpg";
    src[4]=":/Image/5.jpg";
    src[5]=":/Image/6.jpg";
    src[6]=":/Image/7.jpg";
    src[7]=":/Image/8.jpg";
    src[8]=":/Image/9.jpg";
    src[9]=":/Image/10.jpg";
    src[10]=":/Image/11.jpg";
    src[11]=":/Image/12.jpg";
    src[12]=":/Image/13.jpg";
    src[13]=":/Image/14.jpg";
    src[14]=":/Image/15.jpg";
    src[15]=":/Image/16.jpg";
    src[16]=":/Image/17.jpg";
    src[17]=":/Image/18.jpg";
    src[18]=":/Image/19.jpg";
    src[19]=":/Image/20.jpg";
    src[20]=":/Image/21.jpg";
    src[21]=":/Image/22.jpg";
    src[22]=":/Image/23.jpg";
    src[23]=":/Image/24.jpg";
    src[24]=":/Image/25.jpg";
    src[25]=":/Image/26.jpg";
    src[26]=":/Image/27.jpg";
    src[27]=":/Image/28.jpg";
    src[28]=":/Image/29.jpg";
    src[29]=":/Image/30.jpg";
    src[30]=":/Image/31.jpg";
    src[31]=":/Image/32.jpg";
    src[32]=":/Image/33.jpg";
}
Girigiri::~Girigiri()
{

}
void Girigiri::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(src[i]);
    if(i>=32) i=0;
    else i++;
    painter.drawPixmap(0,0,850,550,pix);
}
Logo::Logo(QWidget *parent):QWidget(parent)
{
    this->setFixedSize(200,100);
}
Logo::~Logo()
{

}
void Logo::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/Image/giriep.png");
    painter.drawPixmap(0,0,200,100,pix);
}
