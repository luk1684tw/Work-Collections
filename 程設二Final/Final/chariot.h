#ifndef CHARIOT_H
#define CHARIOT_H
#include <QWidget>

class chariot : public QWidget
{
    Q_OBJECT
public:
    explicit chariot(QWidget *parent = 0);

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *);

};

#endif // CHARIOT_H
