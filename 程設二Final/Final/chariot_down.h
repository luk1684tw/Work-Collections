#ifndef CHARIOT_DOWN_H
#define CHARIOT_DOWN_H
#include <QWidget>

class chariot_down : public QWidget
{
    Q_OBJECT
public:
    explicit chariot_down(QWidget *parent = 0);


signals:

public slots:

protected:
    void paintEvent(QPaintEvent *);

};
#endif // CHARIOT_DOWN_H

