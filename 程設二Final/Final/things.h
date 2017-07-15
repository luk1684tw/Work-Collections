#ifndef ANIMATION_OPEN_H
#define ANIMATION_OPEN_H
#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
class Plane : public QWidget
{
    Q_OBJECT
public:
    explicit Plane(QWidget *parent = 0);
    ~Plane();

protected:
    void paintEvent(QPaintEvent *);

private:

};
class Ball:public QWidget
{
    Q_OBJECT
public:
    explicit Ball(QWidget *parent = 0);
    ~Ball();

protected:
    void paintEvent(QPaintEvent *);
private:
};

class Bang:public QWidget
{
    Q_OBJECT
public:
    explicit Bang(QWidget *parent = 0);
    ~Bang();

protected:
    void paintEvent(QPaintEvent *);
private:
    int i=0;
    QString src[2];
};
class Girigiri:public QWidget
{
    Q_OBJECT
public:
    explicit Girigiri(QWidget *parent = 0);
    ~Girigiri();

protected:
    void paintEvent(QPaintEvent *);
private:
    int i=0;
    QString src[33];
};
class Logo:public QWidget
{
    Q_OBJECT
public:
    explicit Logo(QWidget *parent = 0);
    ~Logo();

protected:
    void paintEvent(QPaintEvent *);
private:
};

#endif // ANIMATION_OPEN_H
