#include "mainwindow.h"
#include <QPixmap>
#include <QPainter>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setFixedSize(850,550);//back size
    ch1 = new chariot(this);
    ch2 = new chariot_up(this);
    ch3 = new chariot_down(this);
    ch4 = new chariot_left(this);

    ch5 = new chariot(this);
    ch6 = new chariot_up(this);
    ch7 = new chariot_down(this);
    ch8 = new chariot_left(this);

    ch8->move(ch8->pos().x()+500,ch8->pos().y());
    ch1->hide();
    ch2->hide();
    ch3->hide();
    ch4->hide();
    ch5->hide();
    ch6->hide();
    ch7->hide();
    ch8->hide();

    button1 = new QPushButton("&Singal Player",this);
    button1->setGeometry(QRect(QPoint(325, 300),QSize(200, 50)));
    connect(button1, SIGNAL (clicked()), this, SLOT (moveButton1()));
    button2 = new QPushButton("&Two Player",this);
    button2->setGeometry(QRect(QPoint(325, 375),QSize(200, 50)));
    connect(button2, SIGNAL (clicked()), this, SLOT (moveButton2()));
    button3 = new QPushButton("&This is not Flappy Bird!!!!!",this);
    button3->setGeometry(QRect(QPoint(275, 450),QSize(300, 50)));
    connect(button3, SIGNAL (clicked()), this, SLOT (moveButton1()));
    //opening animation--ball and plane
    logo = new Logo(this);
    logo->move(325,175);
    plane = new Plane(this);
    plane->move(100,100);
    ball = new Ball(this);
    shot = new Ball(this);
    twoshot = new second(this);
    ball->move(160,115);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(BallAction()));
    shottimer = new QTimer (this);
    shoottimer = new QTimer (this);
    connect(shottimer,SIGNAL(timeout()),this,SLOT(bulletaction()));
    connect(shoottimer,SIGNAL(timeout()),this,SLOT(bulletaction1()));
    timer->start(50);
    shot->hide();
    twoshot->hide();
    //ending animation--girigiri
    //music
    bgm = new easyMusic("Music/girigiri love.mp3",70,1);
    bgm->play();
}
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap background;
    background.load(":/Image/background.jpg");
    painter.drawPixmap(0,0,850,550,background);
}



//control start
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button()==Qt::LeftButton)
    {
        twoshot->move(ch8->pos().x()+42,ch8->pos().y()+42);
        bulletaction1();
    }
}
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Shift)
    {
            shot->move(ch1->pos().x()+42,ch1->pos().y()+42);
            bulletaction();

    }
    else  if(event->key()==Qt::Key_J)
    {
        index = 4;
        ch8->show();
        ch5->hide();
        ch6->hide();
        ch7->hide();
        ch8->move(ch8->pos().x(),ch8->pos().y());
        update();
        chariotaction_left2();
    }
    else  if(event->key()==Qt::Key_I)
    {
        index = 1;
        ch6->show();
        ch5->hide();
        ch7->hide();
        ch8->hide();
        ch6->move(ch8->pos().x(),ch8->pos().y());
        update();
        chariotaction_up2();
    }
    else  if(event->key()==Qt::Key_K)
    {
        index = 3;
        ch7->show();
        ch5->hide();
        ch6->hide();
        ch8->hide();
        ch7->move(ch8->pos().x(),ch8->pos().y());
        update();
        chariotaction_down2();
    }
    else  if(event->key()==Qt::Key_L)
    {
        index = 2;
        ch5->show();
        ch6->hide();
        ch7->hide();
        ch8->hide();
        ch5->move(ch8->pos().x(),ch8->pos().y());
        update();
        chariotaction_right2();
    }


    if(event->key()==Qt::Key_A)
    {
        index = 4;
        ch4->show();
        ch1->hide();
        ch2->hide();
        ch3->hide();
        ch4->move(ch1->pos().x(),ch1->pos().y());
        update();
        chariotaction_left();
    } 
    else  if(event->key()==Qt::Key_W)
    {
        index = 1;
        ch2->show();
        ch1->hide();
        ch3->hide();
        ch4->hide();
        ch2->move(ch1->pos().x(),ch1->pos().y());
        update();
        chariotaction_up();
    }

    else  if(event->key()==Qt::Key_S)
    {
        index = 3;
        ch3->show();
        ch1->hide();
        ch2->hide();
        ch4->hide();
        ch3->move(ch1->pos().x(),ch1->pos().y());
        update();
        chariotaction_down();
    }

    else  if(event->key()==Qt::Key_D)
    {
        index = 2;
        ch1->show();
        ch3->hide();
        ch2->hide();
        ch4->hide();
        ch1->move(ch1->pos().x(),ch1->pos().y());
        update();
        chariotaction_right();
    }

}
//control end

//chariotactions start
void MainWindow::chariotaction_right()
{
   if(ch1->pos().x()>750)
    ch1->move(ch1->pos().x(),ch1->pos().y());
   else
    ch1->move(ch1->pos().x()+10,ch1->pos().y());
}
void MainWindow::chariotaction_left()
{
    if(ch1->pos().x()<0)
    ch1->move(ch1->pos().x(),ch1->pos().y());
    else
    ch1->move(ch1->pos().x()-10,ch1->pos().y());
}
void MainWindow::chariotaction_up()
{
    if(ch1->pos().y()<0)
    ch1->move(ch1->pos().x(),ch1->pos().y());
    else
    ch1->move(ch1->pos().x(),ch1->pos().y()-10);
}
void MainWindow::chariotaction_down()
{
    if(ch1->pos().y()>450)
    ch1->move(ch1->pos().x(),ch1->pos().y());
    else
    ch1->move(ch1->pos().x(),ch1->pos().y()+10);
}
void MainWindow::chariotaction_right2()
{
   if(ch8->pos().x()>750)
    ch8->move(ch8->pos().x(),ch8->pos().y());
   else
    ch8->move(ch8->pos().x()+10,ch8->pos().y());
}
void MainWindow::chariotaction_left2()
{
    if(ch8->pos().x()<0)
    ch8->move(ch8->pos().x(),ch8->pos().y());
    else
    ch8->move(ch8->pos().x()-10,ch8->pos().y());
}
void MainWindow::chariotaction_up2()
{
    if(ch8->pos().y()<0)
    ch8->move(ch8->pos().x(),ch8->pos().y());
    else
    ch8->move(ch8->pos().x(),ch8->pos().y()-10);
}
void MainWindow::chariotaction_down2()
{
    if(ch8->pos().y()>450)
    ch8->move(ch8->pos().x(),ch8->pos().y());
    else
    ch8->move(ch8->pos().x(),ch8->pos().y()+10);
}
// chariotaction end

void MainWindow::moveButton1()
{
    //hide all the objects and start Single player mode;
    button1->hide();
    button2->hide();
    button3->hide();
    logo->hide();
    ball->hide();
    plane->hide();
    timer->stop();
    gameSingle();
}
void MainWindow::moveButton2()
{
    //hide all the objects and start 2P mode;
    button1->hide();
    button2->hide();
    button3->hide();
    logo->hide();
    ball->hide();
    plane->hide();
    timer->stop();
    gameDouble();
}
void MainWindow::BallAction()
{
    int ballx=ball->pos().x()+50;
    if(ballx>=750) ballx=160;
    ball->move(ballx,115);
}
void MainWindow::bulletaction()
{
    shottimer->start(50);
    shot->show();
    if(abs(shot->pos().x()-(ch8->pos().x()+ch8->width()/2))<=30 && abs(shot->pos().y()-(ch8->pos().y()+ch8->height()/2))<=30)
    {
        end_animation();
    }


    if(index==1)
    {
        int balla = shot->pos().y()-50;
        shot->move(shot->pos().x(),balla);
        if(balla<0)
        {
            shottimer->stop();
            shot->hide();
        }
    }
    else if(index==2)
    {
        int balla = shot->pos().x()+50;
        shot->move(balla,shot->pos().y());
        if(balla<0)
        {
            shottimer->stop();
            shot->hide();
        }
    }
    else if(index==3)
    {
        int balla = shot->pos().y()+50;
        shot->move(shot->pos().x(),balla);
        if(balla<0)
        {
            shottimer->stop();
            shot->hide();
        }
    }
    else if(index==4)
    {
        int balla = shot->pos().x()-50;
        shot->move(balla,shot->pos().y());
        if(balla<0)
        {
            shottimer->stop();
            shot->hide();
        }
    }
}

void MainWindow::bulletaction1()
{
    shoottimer->start(50);
    twoshot->show();

    if(abs(twoshot->pos().x()-(ch1->pos().x()+ch1->width()/2))<=30 && abs(twoshot->pos().y()-(ch1->pos().y()+ch1->height()/2))<=30)
    {
        end_animation();
    }


    if(index==1)
    {
        int balla = twoshot->pos().y()-50;
        twoshot->move(twoshot->pos().x(),balla);
        if(balla<0)
        {
            shoottimer->stop();
            twoshot->hide();
        }
    }
    else if(index==2)
    {
        int balla = twoshot->pos().x()+50;
        twoshot->move(balla,twoshot->pos().y());
        if(balla<0)
        {
            shoottimer->stop();
            twoshot->hide();
        }
    }
    else if(index==3)
    {
        int balla = twoshot->pos().y()+50;
        twoshot->move(twoshot->pos().x(),balla);
        if(balla<0)
        {
            shoottimer->stop();
            twoshot->hide();
        }
    }
    else if(index==4)
    {
        int balla = twoshot->pos().x()-50;
        twoshot->move(balla,twoshot->pos().y());
        if(balla<0)
        {
            shoottimer->stop();
            twoshot->hide();
        }
    }
}

void MainWindow::gameSingle()
{
    ch1->show();
    ch1->move(100,220);
    qsrand(time(NULL));
    ch8->move(qrand()%850,qrand()%550);
}
void MainWindow::gameDouble()
{
    ch1->show();
    ch1->move(100,220);
    ch8->show();
}
void MainWindow::end_animation()
{
    giri = new Girigiri(this);
    giri->move(0,0);
    timer->start(50);
    giri->show();
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
}
