#ifndef BULLET_H
#define BULLET_H
#include <QtGui>

class Bullet
{
public:
    Bullet(QPoint SpPoint,int lastAction);
    void draw(QPainter &painter);
    bool move(int w,int h);
    QPoint getPoint();
    int getLast();
private:
    int v = 10;
    QPoint point;
    int r,last;
};

#endif // BULLET_H
