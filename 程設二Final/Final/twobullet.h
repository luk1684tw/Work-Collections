#ifndef ANIMATION_OPEN_H
#define ANIMATION_OPEN_H
#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QTimer>

class twobullet:public QWidget
{
    Q_OBJECT
public:
    explicit twobullet(QWidget *parent = 0);
    ~twobullet();

protected:
    void paintEvent(QPaintEvent *);
private:
};
#endif // TWOBULLET_H
