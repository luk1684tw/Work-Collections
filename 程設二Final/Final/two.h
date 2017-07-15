#ifndef TWO_H
#define TWO_H

#include <QWidget>

class Two:public QWidget
{
    Q_OBJECT
public:
    explicit Two(QWidget *parent = 0);
    ~Ball();

protected:
    void paintEvent(QPaintEvent *);
private:
};

#endif // TWO_H
