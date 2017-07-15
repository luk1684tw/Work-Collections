#ifndef TWOPLAYER_LEFT_H
#define TWOPLAYER_LEFT_H

#include <QWidget>

class twoplayer_left : public QWidget
{
    Q_OBJECT
public:
    explicit twoplayer_left(QWidget *parent = 0);


signals:

public slots:

protected:
    void paintEvent(QPaintEvent *);
};

#endif // TWOPLAYER_LEFT_H
