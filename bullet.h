#ifndef BULLET_H
#define BULLET_H
#include <QtGui>

class Bullet
{
public:
    Bullet(QPoint SpPoint,int lastAction);
    void draw(QPainter &painter);
    bool move(int w,int h);
private:
    int v = 15;
    QPoint point;
    int r,last;
};

#endif // BULLET_H
