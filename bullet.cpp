#include "bullet.h"


Bullet::Bullet(QPoint SpPoint,int lastAction)
{
    point = SpPoint;
    r = 5;
    last = lastAction;
}

void Bullet::draw(QPainter &painter)
{
    if(last==1)
    painter.setBrush(QBrush(QColor(Qt::green)));
    else
    painter.setBrush(QBrush(QColor(Qt::red)));
    painter.drawEllipse(point,r,r)
}

bool Bullet::move(int w, int h)
{
    switch (last) {
        case 1:
            point -= QPoint(0,v);
            break;
        case 2:
            point += QPoint(0,v);
            break;
        default:
            break;
    }
    if(point.x()+r>=w)
    {
        return false;
    }
    if(point.x()-r<=0)
    {
         return false;
    }
    return true;
}