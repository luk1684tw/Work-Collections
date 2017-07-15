#ifndef CHARIOT_LEFT_H
#define CHARIOT_LEFT_H
#include <QWidget>
class chariot_left : public QWidget
{
    Q_OBJECT
public:
    explicit chariot_left(QWidget *parent = 0);


signals:

public slots:

protected:
    void paintEvent(QPaintEvent *);

};

#endif // CHARIOT_LEFT_H
