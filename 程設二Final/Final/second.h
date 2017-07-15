#ifndef SECOND_H
#define SECOND_H
#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QTimer>


class second : public QWidget
{
    Q_OBJECT
public:
    explicit second(QWidget *parent = 0);

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *);
};

#endif // SECOND_H
