#ifndef CHARIOT_UP_H
#define CHARIOT_UP_H
#include <QWidget>

class chariot_up : public QWidget
{
    Q_OBJECT
public:
    explicit chariot_up(QWidget *parent = 0);


signals:

public slots:

protected:
    void paintEvent(QPaintEvent *);

};

#endif // CHARIOT_UP_H

